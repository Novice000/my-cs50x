import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    res = db.execute(
        "SELECT symbol, SUM(shares) AS share FROM transactions  WHERE user_id = ? GROUP BY symbol HAVING share > 0 ORDER BY symbol",
        session["user_id"],
    )

    price_list = []

    for symb in res:
        look = lookup(symb["symbol"])
        item = {
            "symbol": look["symbol"],
            "share": symb["share"],
            "price": look["price"],
            "total": float(look["price"]) * float(symb["share"]),
        }
        price_list.append(item)

    cash = float(
        db.execute("SELECT cash FROM users WHERE id= ?", session["user_id"])[0]["cash"]
    )

    TOTAL = cash
    for price in price_list:
        TOTAL += price["total"]

    if session["user_id"]:
        return render_template("index.html", table=price_list, cash=cash, total=TOTAL)
    else:
        return redirect("/login")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("shares")

        if not symbol or not share:
            return apology("No Symbol and/or Share", 400)

        try:
            float(share)
        except ValueError:
            return apology("Invalid share amount", 400)

        if float(share) <= 0 or ((float(share) % 1 < 1) and (float(share) % 1 > 0)):
            return apology("Invalid share amount", 400)

        sym = lookup(symbol)

        if sym == None:
            return apology("Invalid symbol", 400)

        sym_price = sym["price"]
        price = float(sym_price) * float(share)
        query = db.execute("SELECT * FROM users WHERE id= ?", session["user_id"])

        if float(price) > float(query[0]["cash"]):
            return apology("price exceeds balance")

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, total) values (?,?,?,?,?)",
            session["user_id"],
            sym["symbol"],
            share,
            sym_price,
            price,
        )

        db.execute(
            "update users set cash = ? where id = ?",
            float(query[0]["cash"]) - float(price),
            session["user_id"],
        )

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions")

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol_dic = lookup(symbol)
        if not symbol:
            return apology("No symbol", 400)
        if symbol_dic == None:
            return apology("Symbol not found", 400)
        return render_template(
            "quoted.html", symbol=symbol_dic["symbol"], price=symbol_dic["price"]
        )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Input Username", 400)
        if not password or (password != confirmation):
            return apology("No password or Password mismatch", 400)

        hash_pass = generate_password_hash(password)

        check = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(check) != 0:
            return apology("Username already exist", 400)

        db.execute(
            "INSERT INTO users (username, hash) VALUES ( ?, ? )", username, hash_pass
        )

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("shares")

        if not share or float(share) < 0:
            return apology("Invalid share amount")
        if not symbol:
            return apology("Invalid share amount")

        res = lookup(symbol)
        if res == None:
            return apology("No symbol", 400)

        total = float(res["price"]) * float(share)

        available_shares = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            symbol,
        )[0]["shares"]

        if float(available_shares) < float(share):
            return apology("Exceded available share")

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, total) VALUES (?,?,?,?,?)",
            session["user_id"],
            symbol,
            0 - float(share),
            res["price"],
            total,
        )

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", total, session["user_id"]
        )

        return redirect("/")

    else:
        symbol_diclist = db.execute(
            "SELECT DISTINCT(symbol) AS symbol FROM (SELECT symbol, SUM(shares) AS share FROM transactions WHERE user_id = ? GROUP BY symbol) WHERE share > 0",
            session["user_id"],
        )

        symbols = []
        for s in symbol_diclist:
            symbols.append(s["symbol"])

        return render_template("sell.html", symbols=symbols)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    if request.method == "POST":
        amount = request.form.get("amount")

        if not amount:
            return apology("input an amount")
        try:
            f_amt = float(amount)
        except ValueError:
            return "type in a valid amount"

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", f_amt, session["user_id"]
        )

        return redirect("/")

    else:
        return render_template("add.html")
