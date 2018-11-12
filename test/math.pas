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
		reala, realb: real;
		chara: char;
		texta: text;
		arraya : arr;
		recorda : date;
	begin
		inta := 1;
		intb := 2;

		writeln(((inta << 4 + 2 * intb - intb) / 2) >> 1 % 3);

		/* 4 */
		writeln(6 & 5); 
		/* 7 */
		writeln(5 | 2);
		/* 7 */
		writeln(5 ^ 2);
		/* -1 */
		writeln(~0);
		/* 1 */
		writeln(!0);
	end
.
