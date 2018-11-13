program helloworld;
	type
		int_array = array[1..10] of integer;
		text = array[1..50] of char;
	var inta, intb: integer;
			texta: text;
			arraya: int_array;
	function testInsideFunc(x,y:integer):integer;
		var inta,intb : integer;
		function hello(x,y:integer):integer;
		begin
			if((x != 9) && (y != 2)) then
			begin
				writeln('9 2 line 9 fail');
			end;
		end;
	begin
		if(x != 10) then
		begin
			writeln('line 15 fail');
		end
		else

		hello(9, 2);

		if(y != 1) then
		begin
			writeln('line 20 fail');
		end;
	end;

	function testMixedArg(x:integer;y:text;z:char):integer;
		var inta: integer;
	begin
		inta := 1;

		if(inta != 1) then
		begin
			writeln('1 line 30 fail');
		end;

		if(x != 10) then
		begin
			writeln('10 line 34 fail');
		end;

		if(y[3] != 'c') then
		begin
			writeln('c line 41 fail');
		end;
		
		if(z != 'd') then
		begin
			writeln('d line 46 fail');
		end;
	end;

	function testMixedType:integer;
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
		var a : arr;
				b : date;
				c : days;
				d : colors;
				e : age;
	begin
		a[1] := 1;
		a[2] := 2;
		b.year := 2018;
		b.month := 11;
		b.day := 12;
		c := mon;
		d := blue;
		e := 27;

		if(a[1] != 1) then
		begin
			writeln('1 line 69 fail');
		end;

		if(a[2] != 2) then
		begin
			writeln('2 line 73 fail');
		end;

		if(b.year != 2018) then
		begin
			writeln('2018 line 79 fail');
		end;

		if(b.month != 11) then
		begin
			writeln('11 line 84 fail');
		end;

		if(b.day != 12) then
		begin
			writeln('12 line 89 fail');
		end;

		if(c != mon) then
		begin
			writeln('mon line 94 fail');
		end;

		if(d != blue) then
		begin
			writeln('blue line 99 fail');
		end;

		if(e != 27) then
		begin
			writeln('27 line 104 fail');
		end;
	end;

	function testFunc(x,y:integer):integer;
		var
			k,sum : integer;
	begin
		sum := 1;
		for k:=2 to x div 2 do
		begin
		if x mod k = 0 then 
				begin
						sum := sum + k;
				end;
		end;
		if(sum != 8) then
		begin
			writeln('8 line 135 fail');
		end;
		testFunc := x + y;
	end;

	function testRecurveFunc(x:integer):integer;
	begin
		if(x > 0) then
		begin
			
			testRecurveFunc(x-1);
		end
		else
		begin
			if(x != 0) then
			begin
				writeln('x end fail');
			end;
		end;
	end;

	begin
		texta := 'abafqweradf';
		if(texta[5] != 'q') then
		begin
			writeln('q line 92 fail');
		end;
		testInsideFunc(10, 1);
		testMixedArg(10, 'abcdefg', 'd');
		testMixedType();
		testFunc(10, 1);
		testRecurveFunc(3);
		for inta := 1 to 3 do
		begin
			if(arraya[inta] != 1) then
			begin
				writeln('1 testRecurveFunc fail');
			end;

			if(arraya[inta] != 2) then
			begin
				writeln('2 testRecurveFunc fail');
			end;

			if(arraya[inta] != 3) then
			begin
				writeln('3 testRecurveFunc fail');
			end;
		end

		if(inta != 3) then
		begin
			writeln('3 line 172 fail');
		end;
	end
.
