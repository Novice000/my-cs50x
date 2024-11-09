-- Keep a log of any SQL queries you execute as you solve the mystery.
select * from crime_scene_reports where description like "%duck%";

select * from interviews where transcript like '%bakery%';

select * from bakery_security_logs where day= 28 and month= 7 and year= 2023;

select * from bakery_security_logs where day= 28 and month= 7 and year= 2023 order by license_plate;

select name, activity, people.license_plate from people join bakery_security_logs on people.license_plate = bakery_security_logs.license_plate where day = 28 and month= 7 and year = 2023 and hour = 10 and minute >= 15 and minute <=25;

select name, atm_transactions.account_number, amount from atm_transactions join bank_accounts on atm_transactions.account_number = bank_accounts.account_number join people on bank_accounts.person_id = people.id where day = 28 and month = 7 and year = 2023 and atm_location = 'Leggett Street' and transaction_type='withdraw' and people.license_plate in (select people.license_plate from people join bakery_security_logs on people.license_plate = bakery_security_logs.license_plate where day = 28 and month= 7 and year = 2023 and hour = 10 and minute >= 15 and minute <= 25);

--get name of people from the call clue
select people.name as name, receiver from people join phone_calls on people.phone_number=phone_calls.caller where year = 2023 and month = 7 and day =28 and duration <= 60 and name in (select name from atm_transactions join bank_accounts on atm_transactions.account_number = bank_accounts.account_number join people on bank_accounts.person_id = people.id where day = 28 and month = 7 and year = 2023 and atm_location = 'Leggett Street' and transaction_type='withdraw' and people.license_plate in (select people.license_plate from people join bakery_security_logs on people.license_plate = bakery_security_logs.license_plate where day = 28 and month= 7 and year = 2023 and hour = 10 and minute >= 15 and minute <= 25));

--passengers going out and choosing the earliest
select name, passengers.passport_number, destination_airport_id, full_name from passengers join flights on flights.id = passengers.flight_id join airports on flights.destination_airport_id = airports.id join people on passengers.passport_number = people.passport_number where day = 29 and month= 7 and year = 2023 and name in (select people.name as name from people join phone_calls on people.phone_number=phone_calls.caller where year = 2023 and month = 7 and day =28 and duration <= 60 and name in (select name from atm_transactions join bank_accounts on atm_transactions.account_number = bank_accounts.account_number join people on bank_accounts.person_id = people.id where day = 28 and month = 7 and year = 2023 and atm_location = 'Leggett Street' and transaction_type='withdraw' and people.license_plate in (select people.license_plate from people join bakery_security_logs on people.license_plate = bakery_security_logs.license_plate where day = 28 and month= 7 and year = 2023 and hour = 10 and minute >= 15 and minute <= 25))) order by flights.hour, flights.minute desc;

--get the name of the city
select city from airports where id = 4;

--to get caller and reciever name
select people.name, ess.name from people join phone_calls on phone_calls.caller = people.phone_number join (select name, phone_number from people) as ess on ess.phone_number = phone_calls.receiver where people.name = 'Bruce' and day = 28 and month= 7 and year = 2023 and duration <= 60;
