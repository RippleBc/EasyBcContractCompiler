program helloworld;
	var inta, intb: integer;
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
		var
			sum : integer;
		begin
			sum := x + y;
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
		testFunc(10, 1);
		writeln(1111111111);
		testRecurveFunc(10, 1);
		writeln(1111111111);
		writeln(inta);
	end
.
