program helloworld;
	type
		intarray = array[1..10] of integer;
		days = (sun,mon,tue,wed,thu,fri,sat);
	var
		inta, intb, intc: integer;
		arraya: intarray;
	begin
		if(2 > 1) then
		begin
			if(2 < 1) then
			begin
				writeln('line 11 fail');
			end
			else;
		end
		else writeln('line 9 fail');


		inta := 1;
		intb := 3;
		repeat
		begin
			arraya[inta] := inta;
			inta := inta + 1;
		end
		until (inta > intb);

		if(inta != 4) then
		begin
			writeln('3 repeat num fail');
		end;

		for inta := 1 to 3 do
		begin
			if(inta = 1) then
			begin
				if(arraya[inta] != 1) then
				begin
					writeln('1 repeat fail');
				end;
			end;
			if(inta = 2) then
			begin
				if(arraya[inta] != 2) then
				begin
					writeln('2 repeat fail');
				end;
			end;
			if(inta = 3) then
			begin
				if(arraya[inta] != 3) then
				begin
					writeln('3 repeat fail');
				end;
			end;
		end;


		intb := 10;
		intc := 1;
		for inta := 1 to intb do
		begin
			arraya[intc] := inta;
			intc := intc + 1;
			inta := inta + 3;
		end;

		if(intc != 4) then
		begin
			writeln('3 for num fail');
		end;

		for inta := 1 to 3 do
		begin
			if(inta = 1) then
			begin
				if(arraya[inta] != 1) then
				begin
					writeln('1 for fail');
				end;
			end;
			if(inta = 2) then
			begin
				if(arraya[inta] != 5) then
				begin
					writeln('5 for fail');
				end;
			end;
			if(inta = 3) then
			begin
				if(arraya[inta] != 9) then
				begin
					writeln('9 for fail');
				end;
			end;
		end;


		intb := 1;
		while intb <= 3 do
		begin
			arraya[intb] := intb;
			intb := intb + 1;
		end;

		if(intb != 4) then
		begin
			writeln('3 while num fail');
		end;

		for inta := 1 to 3 do
		begin
			if(inta = 1) then
			begin
				if(arraya[inta] != 1) then
				begin
					writeln('1 while fail');
				end;
			end;
			if(inta = 2) then
			begin
				if(arraya[inta] != 2) then
				begin
					writeln('2 while fail');
				end;
			end;
			if(inta = 3) then
			begin
				if(arraya[inta] != 3) then
				begin
					writeln('3 while fail');
				end;
			end;
		end;
		
		inta := 6;
		intb := 3;
		intc := 3;
		case inta of
			2: 
			begin
			writeln('line 140 fail');
			end;
			5: writeln('line 140 fail');
			6:
				case intb of
					tue: writeln('case control stmt ok\n');
					4: writeln('line 147 fail');
				end;
		end;

	end
.
