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

		inta := ((inta << 4 + 2 * intb - intb) / 2) >> 1 % 3;
		if(inta != 1) then
		begin
			writeln('1 line 27 fail'); 
		end;

		if(6 & 5 != 4) then
		begin
			writeln('4 line 32 fail'); 
		end;

		if(5 | 2 != 7) then
		begin
			writeln('7 line 37 fail'); 
		end;

		if(5 ^ 2 != 7) then
		begin
			writeln('7 line 42 fail'); 
		end;

		if(~0 != -1) then
		begin
			writeln('-1 line 47 fail'); 
		end;

		if(!0 != 1) then
		begin
			writeln('1 line 52 fail'); 
		end;

		uchara := cvuc 'a';
		if(cvi uchara != 97) then
		begin
			writeln('97 line 58 fail'); 
		end;

		uintegera := cvui -1;
		if(uintegera != cvui 4294967295) then
		begin
			writeln('4294967295 line 64 fail'); 
		end;
	end
.
