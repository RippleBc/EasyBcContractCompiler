program helloworld;
	type
		arr = array[1..50] of integer;
		date = record
			year:1900..1999;
			month:1..12;
			day:1..31;
		end;
		days = (sun,mon,tue,wed,thu,fri,sat);
		colors = (red,yellow,blue,white,black,green);
		age = 1..150;
	var
		inta, intb, intc : integer;
		intd : arr;
		inte : date;
	begin
		intd[1] := 10;
		intb := 10 + 20;
		intc := 20;
		inta := ((intb + intc) + 3 * (intb + intc)) / 4 + intd[1] * 2;
		writeln(inta);
	end
.
