//Mythili Karra
//////mmkarra
//////CS101
//////05/8/2019
public class Matrix {
	int length;
	private class Entry {
		int column;
		double value;
		Entry(int x, double y) {
			column = x;
			value = y;
		}
		public boolean equals(Object x) {
			boolean eq = false;
			Entry a;
			if(x instanceof Entry) {
				a = (Entry) x;
				eq = (this.column == a.column && this.value == a.value);
			}
			return eq;
		}
		//insert equals and toString
		public String toString() {
			return "(" + column + ", " + value + ")";
		}
}
	int nonzero;
	List[] array;
	Matrix(int n) {
		if(n<1) {
			throw new RuntimeException("Intended matrix size has to be at least 1");
		}
		length = n;
		nonzero = 0;
		array = new List[n];
		for(int i = 0; i<n;i++) {
			array[i] = new List();
		}	
	}
	int getSize() {
		return length;
	}
	int getNNZ() {
		return nonzero;
	}
	void makeZero() {
		for(int i = 0; i < getSize(); i++) {
			array[i] = new List();
		}
		nonzero = 0;	
	}
	Matrix copy() {
		Matrix M = new Matrix(getSize());
		for(int j = 1; j < array.length + 1;j++) {
			array[j-1].moveFront();
			Entry e;
			while(array[j-1].index() != -1) {
				e = (Entry)array[j-1].get();
				double val = e.value;
				int col = e.column;
				M.changeEntry(j,col,val);
				//	Entry entry = e;
				//	M.array[j].append(entry);
				//append doesnt work append points to the same node so when u alter, the same data changes. WHY DOES CHANGEENTRY WORK THO?i Cuz before you are appending the same node, now you are 
				array[j-1].moveNext();
			}
		}
		M.nonzero = nonzero;
		return M;
	}

	void changeEntry(int i, int j, double x) {
		if(array[i-1].length() == 0) {
			if(x != 0.0) {
			Entry a = new Entry(j,x);
			array[i-1].append(a);
				nonzero++;
			}

		}
		else {
			array[i-1].moveFront();
			Entry entry = (Entry)array[i-1].get();
			boolean search = false;
			int a = 0;
			while(a < array[i-1].length()) {
				if(entry.column == j) {
					search = true;
					break;
				}
				array[i-1].moveNext();
				if(array[i-1].index() != -1) {
					entry = (Entry)array[i-1].get();
				}
				a++;
			}

			//IF SEARCH IS TRUE< THE FOLLOWING WILL BE SKIPPED AND IT WILL GO TO NONZERO STUFF

			if(search == true) {
				if(x == 0.0 && entry.value != 0.0) {
					nonzero--;
					array[i-1].delete();
				}	
				else if(x != 0.0 && entry.value == 0.0) {
					nonzero++;
				}
				entry.value = x;
			}
			else if(search == false && x == 0.0) {
				return;
			}
			else if(search == false) {
				//IF IT DOES NOT EXIST
				array[i-1].moveFront();
				entry = (Entry)array[i-1].get();
				if(j < entry.column) {
					Entry ne = new Entry(j,x);
					array[i-1].prepend(ne);
					array[i-1].movePrev();
				}

				else if(j > entry.column) {
					Entry n = (Entry)array[i-1].get();
					int col = n.column;
					while(array[i-1].index() < array[i-1].length()-1 && col < j) {
						array[i-1].moveNext();
						n = (Entry)array[i-1].get();
						col = n.column;
					}
					Entry ne = new Entry(j,x);
					if(j < col) {
						array[i-1].insertBefore(ne);
						array[i-1].movePrev();
					}
					else {
					array[i-1].insertAfter(ne);
					array[i-1].moveNext();
					}
				}

				entry = (Entry)array[i-1].get();
				if(x == 0.0 && entry.value != 0.0) {
					nonzero--;
				}
				else if(x != 0.0 && entry.value == 0.0) {
					nonzero++;
				}
				else if(x != 0.0 && entry.value != 0.0) {
					nonzero++;
				}
				entry.value = x;
			}
		}
	}

	Matrix scalarMult(double x) {
		Matrix m = new Matrix(getSize()); 
		m = this.copy();
		for(int i = 0;i<m.array.length;i++ ) {
			m.array[i].moveFront();
			for(int j = 0; j < m.array[i].length(); j++ ) {
				Entry entry = (Entry)m.array[i].get();
				entry.value = entry.value*x;
				m.array[i].moveNext();
			}
		}
		return m;
	}

	Matrix add(Matrix M) {
		if(getSize() != M.getSize()) {
			throw new RuntimeException("Both matrices have different sizes");
		}
		Matrix x = new Matrix(getSize());
		if(this.equals(M)) {
			x = M.scalarMult(2);
		}
		else {
			for(int i = 0; i < array.length; i++) {
				array[i].moveFront();
				M.array[i].moveFront();

				while(array[i].index() != -1 && M.array[i].index() != -1) {
					Entry a = (Entry)array[i].get();
					Entry b = (Entry)M.array[i].get();
					if(a.column == b.column) {
						x.changeEntry(i+1,a.column,a.value+b.value);
						array[i].moveNext();
						M.array[i].moveNext();
					}
					else if(a.column < b.column) {
						x.changeEntry(i+1,a.column,a.value);
						array[i].moveNext();
					}
					else  {
						x.changeEntry(i+1,b.column,b.value);
						M.array[i].moveNext();
					}
				}
				if(array[i].index() == -1 && M.array[i].index() != -1) {
					while(M.array[i].index() != -1) {
						Entry n = (Entry)M.array[i].get();
						if(n.value != 0.0) {
							x.array[i].append(n);
							x.nonzero++;
						}
						M.array[i].moveNext();
					}
				}
				else if(M.array[i].index() == -1 && array[i].index() != -1) {
					while(array[i].index() != -1) {      
						Entry n = (Entry)array[i].get();
						if(n.value != 0.0) {
							x.array[i].append(n);
							x.nonzero++;
						}

						array[i].moveNext();
					}
				}
			}
		}
		return x;
	}


	Matrix sub(Matrix M) {
		if(getSize() != M.getSize()) {
			throw new RuntimeException("Both matrices have different sizes");
		}
		Matrix x = new Matrix(getSize());
		if(this.equals(M)) {
			return x;
		}
		else {
			x = M.scalarMult(-1.0);
			Matrix minus = this.add(x);
			return minus;
		}
	}



Matrix transpose() {
	Matrix m = new Matrix(getSize());
	for(int i = 1; i < array.length + 1; i++) {
		array[i-1].moveFront();
		for(int j = 1; j < array[i-1].length() + 1; j++) {
			Entry e = (Entry)array[i-1].get();
			int col = e.column;
			m.changeEntry(col,i,e.value);//doesnt work if m = copy()
			array[i-1].moveNext();
		}
	}
	return m;
}

Matrix mult(Matrix M) {
	if(getSize() != M.getSize()) {
		throw new RuntimeException("Both matrices have different sizes");       
	}
	Matrix m = M.transpose();
	Matrix x = new Matrix(getSize());
	double count = 0.0;
	for(int i = 1; i < array.length + 1; i++) {	
		array[i-1].moveFront();
		m.array[i-1].moveFront();
	if(array[i-1].index() != -1) {
		for(int j=1; j < m.array.length + 1; j++) {
			array[i-1].moveFront();
                        m.array[j-1].moveFront();	
		while(array[i-1].index() != -1 && m.array[j-1].index() != -1) {
				Entry e = (Entry)array[i-1].get();
				Entry en = (Entry)m.array[j-1].get();
				if(e.column == en.column) {
					count = count + (e.value * en.value);
					array[i-1].moveNext();
					m.array[j-1].moveNext();
				}
				else if(e.column < en.column) {
					array[i-1].moveNext();
				}
				else {
					m.array[j-1].moveNext();
				}
		}
			x.changeEntry(i,j,count);
			
			count = 0;
		}	
	}
	}
					return x;


					}

public boolean equals(Object x){
	Matrix a;
	if(x instanceof Matrix){
		a = (Matrix) x;
		if(getSize() != a.getSize()){
			return false;
		}
		for(int i = 1; i <=getSize(); i++){
			if(!(array[i-1].equals(a.array[i-1])))
		//		System.out.println(array[i-1]);
		//		System.out.println(a.array[i-1]);
				return false;
		}
		return true;
	}
	else {
		return false;
	}
}
public String toString(){
	String a = "";
	for(int i = 1; i < array.length + 1; i++) {
		if(array[i-1].length() != 0) {
			a += i+ ": ";
			a += String.valueOf(array[i-1]) + "\n";
		}
	}
	return a;

}
}
