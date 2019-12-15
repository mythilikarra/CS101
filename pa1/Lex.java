//Mythili Karra
////mmkarra
////CS101
////04/15/2019
import java.util.Scanner;
import java.io.*;
public class Lex {
	//why throw IOException
	public static void main (String[] args) throws IOException {
	Scanner in = null;
	PrintWriter out = null;
	if(args.length != 2) {
		System.err.println("Usage: FileIO in out");
		System.exit(1);
	}
	int w = 0;
	int l = 0;
	in = new Scanner(new File(args[0]));
	out = new PrintWriter(new FileWriter(args[1]));
	
	while(in.hasNextLine()) {
		l++;
		in.nextLine();	
		}
		in.close();
		in = null;
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		String[] array = new String[l];
		while(in.hasNextLine()) {
			array[w] = in.nextLine(); 
			w++;
		}	
		//in.close();
//String[] array = {"one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty"};
	//make a list "a"  with indexes of "array"
//	String[] array= {"one","two","three","four","five"};//"six","seven"};
/*	List a = new List();
	for(int x = 0; x < array.length; x++) {
		a.append(x);
	}*/
	List list = new List();
	int i, j;
	String temp;
//	a.moveFront();
	list.append(0);
	list.moveFront();
	for(j = 1; j < array.length; j++) {
		temp = array[j];
		if(j != 1)
//		a.moveNext();
		while(list.index() >= 0 && temp.compareTo(array[list.get()]) < 0) {
			//a.movePrev();
			list.movePrev();
		}

		if(list.index() < 0) {	
			list.prepend(j);
		}
		else {
			if(list.index() != list.length()-1) {
				list.insertAfter(j);
			}
			else {
				list.append(j);
			}
		}
		 list.moveBack();
//	if(a.index() < 0) {
//		a.moveFront();
//	}
//		while(a.index() != j-1) {
//			a.moveNext();
//		}
	}
	list.moveFront();
	while(list.index() > -1) {
		out.println(array[list.get()]);
		list.moveNext();
	}
	in.close();
	out.close();
}
}
