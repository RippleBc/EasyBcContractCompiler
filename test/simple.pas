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
		inta1, inta2: real;
		inta3: char;
		inta4: text;
		intd : arr;
		inte : date;
	begin
		intd[1] := 10;
		intd[2] := 20;
		intd[3] := 30;
		intd[4] := 40;
		intd[5] := 50;
		inte.year := 30;
		inte.month := 5;
		inta := 20;
		intb := 30;
		intc := ((intb + inta) + 3 * (intb + inta)) / 4 + intd[2] * 2 + inte.month + intd[1];
		writeln(intc);
		writeln('###################');

		inta1 := 1.23;
		inta2 := inta1 + 1.56;
		writeln(inta2);
		writeln('###################');

		inta3 := 'a';
		writeln(inta3);
		writeln('###################');

		inta4 := 'abcdefg';
		writeln(inta4[3]);
		writeln('###################');
	end
.
