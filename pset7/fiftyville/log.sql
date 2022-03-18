-- Keep a log of any SQL queries you execute as you solve the mystery.

Select description from crime_scene_reports
where
    day = "28" and month = "7" and year = "2020" and street = "Chamberlin Street"

Select transcript from interviews
where
    day = "28" and month = "7" and year = "2020" and transcript like "%courthouse%"

Select activity from courthouse_security_logs

Select name from people join courthouse_security_logs on people.license_plate = courthouse_security_logs.license_plate
where
    day = "28" and month = "7" and year = "2020" and hour = "10" and minute >= "15" and minute < "25" and activity = "exit"

Select DISTINCT name from people join bank_accounts on people.id = bank_accounts.person_id join atm_transactions on bank_accounts.account_number = atm_transactions.account_number
where
    day = "28" and month = "7" and year = "2020" and transaction_type = "withdraw" and atm_location = "Fifer Street"

Select name from people join passengers on people.passport_number = passengers.passport_number
where flight_id = (select id from flights where
                                            day = "29" and month = "7" and year = "2020" order by hour, minute limit 1)

Select name from people join phone_calls on people.phone_number = phone_calls.caller
Where
    day = "28" and month = "7" and year = "2020" and duration < "60"

Select name from people join passengers on people.passport_number = passengers.passport_number
where
    flight_id = (Select id from flights where
                                            day = "29" and month = "7" and year = "2020" order by hour, minute limit 1)
INTERSECT

Select DISTINCT name from people join bank_accounts on people.id = bank_accounts.person_id join atm_transactions on bank_accounts.account_number = atm_transactions.account_number
where
    day = "28" and month = "7" and year = "2020" and transaction_type = "withdraw" and atm_location = "Fifer Street"
INTERSECT

Select name from people join phone_calls on people.phone_number = phone_calls.caller
Where
    day = "28" and month = "7" and year = "2020" and duration < "60"
INTERSECT

Select name from people join courthouse_security_logs on people.license_plate = courthouse_security_logs.license_plate
where
    day = "28" and month = "7" and year = "2020" and hour = "10" and minute >= "15" and minute < "25" and activity = "exit"

Select city from airports
where
    id = (select destination_airport_id from flights where
                                                        day = "29" and month = "7" and year = "2020" order by hour, minute limit 1)
Select name from people join phone_calls on people.phone_number = phone_calls.receiver
where
    day = "28" and month = "7" and year = "2020" and duration < "60" and caller = (select phone_number from people where name = "Ernest");
