//Mythili Karra
//////mmkarra
//////CS101
//////05/8/2019
import java.io.*;
import java.util.Scanner;

public class Sparse {
	public static void main (String[]args) throws IOException{
	if (args.length < 2) {
			throw new RuntimeException ("Usage: infile outfile");
		}
	Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(args[1]);
	int x = in.nextInt();
	Matrix A = new Matrix(x);
	Matrix B = new Matrix(x);
	int one = in.nextInt();
	int two = in.nextInt();
	in.nextLine();
	for(int i = 0; i < one; i++) {
		int row = in.nextInt();
		int column = in.nextInt();
		double value = in.nextDouble();
		A.changeEntry(row,column,value);
	}
	in.nextLine();
	for(int j = 0; j < two; j++) {
		int row = in.nextInt();
                int column = in.nextInt();
                double value = in.nextDouble();
                B.changeEntry(row,column,value);
	}
	out.println("A has " + one + " non-zero entries:");
	out.println(A);
	out.println("B has " + two + " non-zero entries:");
        out.println(B);
	out.println("(1.5) * A = ");
	out.println(A.scalarMult(1.5));
	out.println("A + B = ");
	out.println(A.add(B));
	out.println("A + A = ");
	out.println(A.add(A));
	out.println("B - A = ");
	out.println(B.sub(A));
	out.println("A - A = ");
	out.println(A.sub(A));
	out.println("Transpose(A) = ");
	out.println(A.transpose());
	out.println("A * B = ");
	out.println(A.mult(B));
	out.println("B * B = ");
	out.println(B.mult(B));
	in.close();
	out.close();
	return;
	}
}

