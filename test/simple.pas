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
		writeln('year %d month %d like %s zzzz\n', 2018, 11, 'apple');

		inta := 1;
		intb := 2;
		intc := -2;

		/*  */
		recorda.year := 1990;
		recorda.month := 11;
		recorda.day := 12;

		writeln('%d\n', recorda.year);
		writeln('%d\n', recorda.month);
		writeln('%d\n', recorda.day);
		
		/* 'a' 'c' */
		texta := 'abcdefg';
		writeln('%c\n', texta[1]);
		writeln('%c\n', texta[3]);


		/* 'c' 'm' */
		texta[10] := 'm';
		writeln('%c\n', texta[3]);
		writeln('%c\n', texta[10]);

		/* 10 */
		inta := ((inta << 4 + 2 * intb - intb) / 2) >> 1 % 3 + intc + recorda.month;
		if(inta != 10) then
		begin
			writeln('%d\n', -1);
		end;

		/* if else 1 2 3 4 5 6 7 */
		if(2 > 1) then
		begin
			if(2 < 1) then
			begin
				writeln('%d\n', -1);
			end
			else
			begin
				writeln('%d\n', 1);
			end;

			if(2 >= 1) then
			begin
				writeln('%d\n', 2);
			end
			else
			begin
				writeln('%d\n', -1);
			end;

			if(2 <= 1) then
			begin
				writeln('%d\n', -1);
			end
			else
			begin
				writeln('%d\n', 3);
			end;

			if(1 = 1) then
			begin
				writeln('%d\n', 4);
			end
			else
			begin
				writeln('%d\n', -1);
			end;

			if(3 = 1) then
			begin
				writeln('%d\n', -1);
			end
			else
			begin
				writeln('%d\n', 5);
			end;

			if(3 != 1) then
			begin
				writeln('%d\n', 6);
			end
			else
			begin
				writeln('%d\n', -1);
			end;

			if(1 != 1) then
			begin
				writeln('%d\n', -1);
			end
			else
			begin
				writeln('%d\n', 7);
			end;
		end
		else writeln('%d\n', -1);


		/* repeat 1 2 3 */
		inta := 1;
		intb := 3;
		repeat
		begin
			arraya[inta] := inta;
			writeln('%d\n', arraya[inta]);
			inta := inta + 1;
		end
		until (inta > intb);

		if(inta != 4) then
		begin
			writeln('%d\n', -1);
		end;

		for inta := 1 to 3 do
		begin
			if(inta = 1) then
			begin
				if(arraya[inta] != 1) then
				begin
					writeln('%d\n', -1);
				end;
			end;
			if(inta = 2) then
			begin
				if(arraya[inta] != 2) then
				begin
					writeln('%d\n', -1);
				end;
			end;
			if(inta = 3) then
			begin
				if(arraya[inta] != 3) then
				begin
					writeln('%d\n', -1);
				end;
			end;
		end;

		/* for 1 5 9 */
		intb := 10;
		intc := 1;
		for inta := 1 to intb do
		begin
			arraya[intc] := inta;
			writeln('%d\n', arraya[intc]);
			intc := intc + 1;
			inta := inta + 3;
		end;

		if(intc != 4) then
		begin
			writeln('%d\n', -1);
		end;

		for inta := 1 to 3 do
		begin
			if(inta = 1) then
			begin
				if(arraya[inta] != 1) then
				begin
					writeln('%d\n', -1);
				end;
			end;
			if(inta = 2) then
			begin
				if(arraya[inta] != 5) then
				begin
					writeln('%d\n', -1);
				end;
			end;
			if(inta = 3) then
			begin
				if(arraya[inta] != 9) then
				begin
					writeln('%d\n', -1);
				end;
			end;
		end;

		/* while 1 2 3 */
		intb := 1;
		while intb <= 3 do
		begin
			arraya[intb] := intb;
			writeln('%d\n', arraya[intb]);
			intb := intb + 1;
		end;

		if(intb != 4) then
		begin
			writeln('%d\n', -1);
		end;

		for inta := 1 to 3 do
		begin
			if(inta = 1) then
			begin
				if(arraya[inta] != 1) then
				begin
					writeln('%d\n', -1);
				end;
			end;
			if(inta = 2) then
			begin
				if(arraya[inta] != 2) then
				begin
					writeln('%d\n', -1);
				end;
			end;
			if(inta = 3) then
			begin
				if(arraya[inta] != 3) then
				begin
					writeln('%d\n', -1);
				end;
			end;
		end;
		
		/* case 1 */
		inta := 6;
		intb := 3;
		intc := 3;
		case inta of
			2: 
			begin
			writeln('%d\n', -1);
			end;
			5: writeln('%d\n', -1);
			6:
				case intb of
					tue: writeln('%d\n', 1);
					4: writeln('%d\n', -1);
				end;
		end;
	end
.
