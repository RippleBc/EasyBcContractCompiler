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
		writeln('%d\n', intc);
		
		reala1 := 1.23;
		reala2 := reala1 + 1.56;
		writeln('%f\n', reala2);

		chara := 'a';
		writeln('%c\n', chara);

		writeln('%s\n', 'abcdefg');
		writeln('%s\n', 'abcdefgafadfafadfafasfadf');
		writeln('%s\n', 'abcdefg');

		writeln('%f\n', 1.234);

		stringa := 'abcdefgafadfafadfafasfadf';
		writeln('%c\n', stringa[5]);

		booleana := true;
		readln('%d', intd[1]);
		readln('%c', chara);
		readln('%d', booleana);
		readln('%f', reala2);
		writeln('%d %c %d %f\n', intd[1], chara, booleana, reala2);
	end
.
