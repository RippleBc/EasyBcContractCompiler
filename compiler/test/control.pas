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

		/* writeln(9876543210); */
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
		writeln('###################');

		inta := 1;
		intb := 10;
		repeat
		begin
			inta := inta + 1;
			writeln(inta);
		end
		until (inta > intb);
		writeln('###################');

		intb := 10;
		for inta := 1 to intb do
		begin
			writeln(inta);
			inta := inta + 3;
		end;
		writeln('###################');

		intb := 1;
		while intb <= 10 do
		begin
			writeln(intb);
			intb := intb + 1;
		end;
		writeln('###################');
		
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
		writeln('###################');
	end
.
