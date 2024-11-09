import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name=  request.form.get('name')
        month=  request.form.get('month')
        day=  request.form.get('day')

        if not name or not month or not day:
            return redirect('/')


        try:
            int(day)
            if int(day) >= 1 and int(day) <= 31:
                pass
            else:
                return redirect('/')
        except ValueError:
                return redirect('/')



        try:
            int(month)
            if int(month) >= 1 and int(month) <= 12:
                pass
            else:
                 return redirect('/')
        except ValueError:
                return redirect('/')


        if int(day) > 29 and int(month) == 2:
            return redirect('/')

        if int(day) > 30 and int(month) not in [9,4,6,11]:
            return redirect('/')

        if int(day) > 31 and int(month) not in [1,3,5,7,8,10,12]:
            return redirect('/')

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?,?,?)", name, month, day)
        return redirect("/")

        # TODO: Display the entries in the database on index.html
    else:
        birthdays = db.execute('SELECT * FROM birthdays')
        return render_template("index.html", birthdays= birthdays)


@app.route('/delete', methods= ["POST"])
def delete():
    id = request.form.get('id')
    db.execute('DELETE FROM birthdays WHERE id = ?', id)
    return redirect('/')
