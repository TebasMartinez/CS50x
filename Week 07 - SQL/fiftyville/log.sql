-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND street = 'Humphrey Street';
-- Thanks to that query, I now know that:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- Check the interviews on the day of the crime
SELECT name, transcript
FROM interviews
WHERE year = 2024
AND month = 7
AND day = 28;

-- Acording to the interviews:
-- The thief drove away 10 minutes after the crime.
-- Before the crime, the thief was withdrwing money from the ATM on Leggett Street.
-- Right after the crime, the thief told someone on the phone to buy plane tickets for the day after.
-- Suspects: Robert and Patrick, sons of Lily. They took a rooster to Paris.

-- Undertsand info in bakery_security_logs
SELECT * FROM bakery_security_logs LIMIT 5;

-- Check bakery security log for the day of the crime.
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2024 AND hour IN (9, 10, 11);

-- Check ATM transactions for the of the crime
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street';

-- Check who made those transactions
SELECT DISTINCT name, phone_number, passport_number, license_plate FROM bank_accounts
JOIN people ON people.id = person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street');

-- Out of the people who made transactions, select those who were in the backery on the day of the crime
SELECT name, phone_number, passport_number, hour, minute, activity, bakery_security_logs.license_plate FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE month = 7 AND day = 28 AND year = 2024 AND bakery_security_logs.license_plate IN
(SELECT DISTINCT license_plate FROM bank_accounts
JOIN people ON people.id = person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street'));

--Check flights for the day after the crime from Fiftyville
SELECT
origin.city AS origin,
destination.city AS destination,
flights.id,
month, day, hour, minute
FROM flights
JOIN airports origin ON origin.id = origin_airport_id
JOIN airports destination ON destination.id = destination_airport_id
WHERE year = 2024 AND month = 7 AND day = 29
AND origin.city = 'Fiftyville'
ORDER BY hour;

-- List of passangers in flights for the day after the crime from Fiftyville
SELECT name, phone_number, people.passport_number
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE passengers.flight_id IN
(SELECT
flights.id
FROM flights
JOIN airports origin ON origin.id = origin_airport_id
JOIN airports destination ON destination.id = destination_airport_id
WHERE year = 2024 AND month = 7 AND day = 29
AND origin.city = 'Fiftyville'
ORDER BY hour);

-- Out of these people on flights the 29th, choose those who were in the bakery and made transactions the 28th
SELECT name, phone_number, people.passport_number
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE passengers.flight_id IN
(SELECT flights.id FROM flights
JOIN airports origin ON origin.id = origin_airport_id
JOIN airports destination ON destination.id = destination_airport_id
WHERE year = 2024 AND month = 7 AND day = 29 AND origin.city = 'Fiftyville' ORDER BY hour)
AND people.passport_number IN
(SELECT people.passport_number FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE month = 7 AND day = 28 AND year = 2024 AND bakery_security_logs.license_plate IN
(SELECT DISTINCT license_plate FROM bank_accounts
JOIN people ON people.id = person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street')));

-- Out of those people, check phone calls on the 28th. Only those who **withdraw** money at the ATM
SELECT calling.name, receiving.name, duration FROM phone_calls
JOIN people calling ON phone_calls.caller = calling.phone_number
JOIN people receiving ON phone_calls.receiver = receiving.phone_number
WHERE year = 2024 AND month = 7 AND day = 28
AND caller IN
    (SELECT phone_number
    FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    WHERE passengers.flight_id IN
        (SELECT flights.id FROM flights
        JOIN airports origin ON origin.id = origin_airport_id
        JOIN airports destination ON destination.id = destination_airport_id
        WHERE year = 2024 AND month = 7 AND day = 29 AND origin.city = 'Fiftyville' ORDER BY hour)
    AND people.passport_number IN
        (SELECT people.passport_number FROM bakery_security_logs
        JOIN people ON people.license_plate = bakery_security_logs.license_plate
        WHERE month = 7 AND day = 28 AND year = 2024 AND bakery_security_logs.license_plate IN
            (SELECT DISTINCT license_plate FROM bank_accounts
            JOIN people ON people.id = person_id
            JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
            WHERE bank_accounts.account_number IN
                (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))));

-- Only those who left the bakery between 10:15 and 10:30 am
SELECT calling.name, receiving.name, duration FROM phone_calls
JOIN people calling ON phone_calls.caller = calling.phone_number
JOIN people receiving ON phone_calls.receiver = receiving.phone_number
WHERE year = 2024 AND month = 7 AND day = 28
AND caller IN
    (SELECT phone_number
    FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    WHERE passengers.flight_id IN
        (SELECT flights.id FROM flights
        JOIN airports origin ON origin.id = origin_airport_id
        JOIN airports destination ON destination.id = destination_airport_id
        WHERE year = 2024 AND month = 7 AND day = 29 AND origin.city = 'Fiftyville' ORDER BY hour)
    AND people.passport_number IN
        (SELECT people.passport_number FROM bakery_security_logs
        JOIN people ON people.license_plate = bakery_security_logs.license_plate
        WHERE month = 7 AND day = 28 AND year = 2024 AND hour = 10 AND minute > 15 AND minute < 30
        AND bakery_security_logs.license_plate IN
            (SELECT DISTINCT license_plate FROM bank_accounts
            JOIN people ON people.id = person_id
            JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
            WHERE bank_accounts.account_number IN
                (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))));

-- Since only Bruce and Diana are the suspects, check what time did they leave the bakery
SELECT * FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7 AND day = 28 AND year = 2024 AND hour = 10 AND minute > 15 AND minute < 30
AND people.name IN
    (SELECT calling.name FROM phone_calls
    JOIN people calling ON phone_calls.caller = calling.phone_number
    JOIN people receiving ON phone_calls.receiver = receiving.phone_number
    WHERE year = 2024 AND month = 7 AND day = 28
    AND caller IN
        (SELECT phone_number
        FROM people
        JOIN passengers ON passengers.passport_number = people.passport_number
        JOIN flights ON flights.id = passengers.flight_id
        WHERE passengers.flight_id IN
            (SELECT flights.id FROM flights
            JOIN airports origin ON origin.id = origin_airport_id
            JOIN airports destination ON destination.id = destination_airport_id
            WHERE year = 2024 AND month = 7 AND day = 29 AND origin.city = 'Fiftyville' ORDER BY hour)
        AND people.passport_number IN
            (SELECT people.passport_number FROM bakery_security_logs
            JOIN people ON people.license_plate = bakery_security_logs.license_plate
            WHERE month = 7 AND day = 28 AND year = 2024 AND hour = 10 AND minute > 15 AND minute < 30
            AND bakery_security_logs.license_plate IN
                (SELECT DISTINCT license_plate FROM bank_accounts
                JOIN people ON people.id = person_id
                JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
                WHERE bank_accounts.account_number IN
                    (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')))));

-- Bruce left the bakery only at 10:18, so the thief is Diana, who left at 10:23, and her accomplice is Philip
-- Check where she went
SELECT
origin.city AS origin,
destination.city AS destination,
flights.id,
month, day, hour, minute
FROM flights
JOIN airports origin ON origin.id = origin_airport_id
JOIN airports destination ON destination.id = destination_airport_id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE year = 2024 AND month = 7 AND day = 29
AND origin.city = 'Fiftyville'
AND name = 'Diana';

-- After using check50 and checking I was wrong, the thief must be Bruce, and he just left the bakery at 10:18
-- Check where he went
SELECT
origin.city AS origin,
destination.city AS destination,
flights.id,
month, day, hour, minute
FROM flights
JOIN airports origin ON origin.id = origin_airport_id
JOIN airports destination ON destination.id = destination_airport_id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE year = 2024 AND month = 7 AND day = 29
AND origin.city = 'Fiftyville'
AND name = 'Bruce';

-- The only person Bruce spoke with for under a minute is Robin!!!
