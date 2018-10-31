program helloworld;
	type text = array[1..50] of char;
	var inta, intb: integer;
	function testInsideFunc(x,y:integer):integer;
		var inta,intb : integer;
		function hello(x,y:integer):integer;
		begin;
			writeln(x);
			writeln(y);
			inta := 5;
			writeln(inta);
		end;
	begin
		writeln(x);
		hello(9, 2);
		writeln(y);
	end;

	function testMixedArg(x:integer;y:text):integer;
		var inta : integer;
	begin
		inta := 1;
		writeln(inta);
		writeln(x);
		writeln(y[3]);
	end;

	function testMixedType(x,y:integer):integer;
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
		writeln(a[1]);
		writeln(a[2]);
		writeln(b.year);
		writeln(b.month);
		writeln(b.day);
		writeln(c);
		writeln(d);
		writeln(e);
	end;
	function testFunc(x,y:integer):integer;
		var
			k,sum : integer;
	begin
		sum := 1;
		for k:=2 to x div 2 do
		begin
		writeln(k);
		if x mod k = 0 then 
				begin
						sum := sum + k;
				end;
		end;
		writeln(sum);
		testFunc := x + y;
	end;
	function testRecurveFunc(x,y:integer):integer;
	begin
		if(x > 0) then
		begin
			writeln(x);
			testRecurveFunc(x-1, y);
		end
		else
			writeln(1000);
		testRecurveFunc := x + y;
	end;
	begin
		testInsideFunc(10, 1);
		writeln(1111111111);
		testMixedArg(10, 'abcdefg');
		writeln(1111111111);
		testMixedType(10, 1);
		writeln(1111111111);
		testFunc(10, 1);
		writeln(1111111111);
		testRecurveFunc(10, 1);
		writeln(1111111111);
		inta := 2;
		writeln(inta);
	end
.
