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
		inta := ((intb + intc) + 3 * (intb + intc)) / 4 + intd[2] * 2 + inte.month + intd[1];
		writeln(inta);
		writeln(1234567890);

		if(2 > 1) then
		begin
			writeln(1);
			if(2 < 1) then
			begin
				writeln(1);
			end
			else writeln(0);
		end
		else writeln(0);
		writeln(1234567890);

		inta := 1;
		intb := 10;
		repeat
		begin
			inta := inta + 1;
			writeln(inta);
		end
		until (inta > intb);
		writeln(1234567890);

		intb := 10;
		for inta := 1 to intb do
		begin
			writeln(inta);
			inta := inta + 3;
		end;
		writeln(1234567890);

		intb := 1;
		while intb <= 10 do
		begin
			writeln(intb);
			intb := intb + 1;
		end;
		writeln(1234567890);
		
		inta := 6;
		intb := 3;
		intc := 3;
		case inta of
			2: 
			begin
			writeln(2);
			end;
			5: writeln(5);
			6:
				case intb of
					tue: 
					begin
					writeln(3);
					end;
					4: writeln(4);
				end;
		end;

		writeln(inte.year);
	end
.
