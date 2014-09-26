/* Date.cpp
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#include "Date.h"

#include <cstring>

using namespace std;

namespace {
	// Only allow Dates to step by whole-day increments.
	static const time_t SECONDS_PER_DAY = 60 * 60 * 24;
	static const double SECONDS_TO_DAYS = 1. / SECONDS_PER_DAY;
	
	// The string will never be longer than 29 characters, plus a '\0'.
	static const size_t MAX_SIZE = 32;
}



Date::Date()
	: today(0), str(MAX_SIZE, '\0')
{
}



Date::Date(int day, int month, int year)
	: str(MAX_SIZE, '\0')
{
	tm t;
	memset(&t, 0, sizeof(t));
	t.tm_hour = 12;
	t.tm_mday = day;
	t.tm_mon = month - 1;
	t.tm_year = year - 1900;
	today = mktime(&t);
}



const string &Date::ToString() const
{
	if(str.size() == MAX_SIZE)
	{
		// Convert to a tm structure (day of the week, etc.).
		tm t;
		gmtime_r(&today, &t);
	
		size_t length = strftime(&str.front(), MAX_SIZE, "%a, %-d %b %Y", &t);
		str.resize(length);
	}
	
	return str;
}



string Date::LongString() const
{
	tm t;
	gmtime_r(&today, &t);
	string result = "the " + to_string(t.tm_mday);
	if(t.tm_mday / 10 == 1 || t.tm_mday % 10 == 0 || t.tm_mday % 10 > 3)
		result += "th";
	else if(t.tm_mday % 10 == 1)
		result += "st";
	else if(t.tm_mday % 10 == 2)
		result += "nd";
	else
		result += "rd";
	
	result += " of ";
	static const string MONTH[12] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	result += MONTH[t.tm_mon];
	
	return result;
}



void Date::operator++()
{
	today += SECONDS_PER_DAY;
	
	// Flag ToString() that the conversion must be done over.
	str.resize(MAX_SIZE);
}



void Date::operator++(int)
{
	++*this;
}



Date Date::operator+(int days) const
{
	Date result;
	result.today = today + days * SECONDS_PER_DAY;
	return result;
}



bool Date::operator<(const Date &other) const
{
	tm t;
	gmtime_r(&today, &t);
	
	tm ot;
	gmtime_r(&other.today, &ot);
	
	if(t.tm_year < ot.tm_year)
		return true;
	if(t.tm_year > ot.tm_year)
		return false;
	
	if(t.tm_mon < ot.tm_mon)
		return true;
	if(t.tm_mon > ot.tm_mon)
		return false;
	
	return t.tm_mday < ot.tm_mday;
}



// Get the number of days that have elapsed since the "epoch".
double Date::DaysSinceEpoch() const
{
	return today * SECONDS_TO_DAYS;
}



// Get the date as numbers.
int Date::Day() const
{
	tm t;
	gmtime_r(&today, &t);
	
	return t.tm_mday;
}



int Date::Month() const
{
	tm t;
	gmtime_r(&today, &t);
	
	return t.tm_mon + 1;
}



int Date::Year() const
{
	tm t;
	gmtime_r(&today, &t);
	
	return t.tm_year + 1900;
}
