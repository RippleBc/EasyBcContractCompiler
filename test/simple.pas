program helloworld;
	type
		arr = array[1..50] of integer;
		text = array[1..50] of char;
		date = record
			year:1900..1999;
			month:1..12;
			day:1..31;
		end;
		days = (sun,mon,tue,wed,thu,fri,sat);
		colors = (red,yellow,blue,white,black,green);
		age = 1..150;
	var
		inta, intb, intc: integer;
		uintegera: uinteger;
		reala, realb: real;
		chara: char;
		uchara: uchar;
		texta: text;
		arraya : arr;
		recorda : date;
	begin
		inta := 1;
		intb := 2;
		intc := -2;

		/* -1 */
		inta := ((inta << 4 + 2 * intb - intb) / 2) >> 1 % 3 + -2;

		writeln('%d', inta);
	end
.
