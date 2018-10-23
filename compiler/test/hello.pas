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
		intd[2] := 20;
		intd[3] := 30;
		intd[4] := 40;
		intd[5] := 50;
		intb := 10 + 20;
		intc := 20;
		inte.year := 30;
		inte.month := 5;
		inta := ((intb + intc) + 3 * (intb + intc)) / 4 + intd[2] * 2 + inte.month;
		writeln(inta);

		if(1) then
		begin
			writeln(1);
			if(0) then
			begin
				writeln(1);
			end
			else writeln(0);
		end
		else writeln(0);

		




		writeln(100);
	end
.
