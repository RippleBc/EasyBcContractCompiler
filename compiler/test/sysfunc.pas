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
		reala1, reala2: real;
		chara: char;
		stringa: text;
		intd : arr;
		inte : date;
		booleana : boolean;
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
		writeln(1234567890);
		
		reala1 := 1.23;
		reala2 := reala1 + 1.56;
		writeln(reala2);
		writeln(1234567890);

		chara := 'a';
		writeln(chara);
		writeln(1234567890);

		writeln('abcdefg');
		writeln('abcdefgafadfafadfafasfadf');
		writeln('abcdefg');
		writeln(1234567890);

		writeln(1.234);
		writeln(1234567890);

		stringa := 'abcdefgafadfafadfafasfadf';
		writeln(stringa[5]);
		writeln(1234567890);
		
		booleana := true;
		readln(intd[1]);
		writeln(intd[1], chara, booleana, reala2, 'abdqrgadfq');
	end
.
