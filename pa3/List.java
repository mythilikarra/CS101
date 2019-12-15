public class List {
	private class Node {
		Object value;
		Node next;
		Node previous;

		Node(Object data) {
			value = data;
			next = null;
			previous = null;
		}
		public String toString() {
			String s = String.valueOf(value);
			return s;

		}

	}
	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int indexcursor;
	public List() {
		length = 0;
		indexcursor = -1;
		front = null;
		back = null;
		cursor = null;
	}
	int length() {
		return length;
	}
	int index() {
		return indexcursor;
	}
	Object front() {
		if(length() > 0) //can u do just length?
			return front.value;
		else {
			throw new RuntimeException("front() called on an empty list");

		}
	}
	Object back() {
		if(length() > 0)
			return back.value;
		else {
			throw new RuntimeException("back() called on an empty list");
		}
	}
	Object get() {
		if(length>0 && indexcursor >=0) {
			return cursor.value;
		}
		else {
			throw new RuntimeException("get() called when there is no cursor element");
		}
	}
	public boolean equals(List L) {
		if(length != L.length) {
			return false;
		}
		else if(length == 0) {
			return true;
		}
		else {
			Node a = front;
			Node b = L.front;
			while(a != null) {
				if(!(a.value.equals(b.value))) {
					return false;
				}
				else {
					a = a.next;
					b = b.next;
				}
			}
		}
		return true;
	}

	void clear() {
		front = null;
		back = null;
		cursor = null;
		length = 0;
		indexcursor = -1;
	}
	void moveFront() {
		if(length() > 0) {
			cursor = front;
			indexcursor = 0;
		}
	}
	void moveBack() {
		if(length() > 0) {
			cursor = back;
			indexcursor = length-1;
		}
	}
	void moveNext() {
		if(cursor != null && cursor != back) {
			Node a = cursor;
			Node b = cursor.next.next;
			cursor = cursor.next;
			cursor.previous = a;
			cursor.next = b;
			indexcursor++;
		}
		else if(cursor != null && indexcursor == length - 1) {
			cursor = null;
			indexcursor = -1;
		}
	}
	void movePrev() {
		if(cursor != null) {
			if(indexcursor != 0 && indexcursor != 1) {
				Node a = cursor.previous.previous;
				Node b = cursor;
				cursor = cursor.previous;
				cursor.previous = a;
				cursor.next = b;
				indexcursor--;
			}
			else if(indexcursor == 0) {
				cursor = null;
				indexcursor = -1;
			}
			else if(indexcursor == 1) {
				Node a = cursor;
				cursor = cursor.previous;
				indexcursor = 0;
				if(indexcursor != length() - 1) {
					a.previous = cursor;
				}
				if(indexcursor != 0) {
					cursor.previous = null;
				}
			}
		}
		else if(cursor == null) {
			throw new RuntimeException("Cannot move cursor when cursor is undefined");
		}
	}
	void prepend(Object data) {
		if(length() > 0) {
			Node temp = front;
			Node N = new Node(data);
			front = N;
			front.next = temp;
			front.previous = null;
			temp.previous = front;
		}
		if(length() == 0) {
			Node N = new Node(data);
			front = N;
			back = N;
		}
		if(indexcursor != -1) {
			indexcursor++;
		}
		length++;
	}
	void append(Object data) {
		if(length() > 0) {
			Node temp = back;
			Node N = new Node(data);
			back = N;
			temp.next = N;
			N.previous = temp;
		}
		if(length() == 0) {
			Node N = new Node(data);
			front = N;
			back = N;
		}
		length++;
	}
	void insertBefore(Object data) {
		if(length() > 0 && index()>=0) {
			if(cursor.previous == null) {
				Node N = new Node(data);
				N.next = front;
				front = N;
				cursor.previous = N;
				N.previous = front;
				length++;
			}
			else {
				Node temp = cursor.previous;
				Node N = new Node(data);
				temp.next = N;
				N.next = cursor;
				cursor.previous = N;
				N.previous = temp;
				length++;
			}
			indexcursor++;
		}

	}
	void insertAfter(Object data) {
		if(length() > 0 && index()>=0) {
			//if next value is null will I get an error?            
			//Answer: yes
			if(cursor.next != null) {
				Node temp = cursor.next;
				Node N = new Node(data);
				cursor.next = N;
				N.next = temp;
				N.previous = cursor;
				temp.previous = N;
				length++;
			}
			else {
				Node N = new Node(data);
				cursor.next = N;
				N.previous = cursor;
				back = N;
				length++;
			}
		}
		else {
			throw new RuntimeException("Cannot insert when a cursor is not defined");
		}
	}
	void deleteFront() {
		if(length() == 1) {
			clear();
		}
		else if(length() >1) {
			front = front.next;
			front.previous = null;
			length--;
		}
		else if (length() == 0) {
			throw new RuntimeException("Cannot delete from an empty list");
		}
		if(indexcursor != -1) {
			indexcursor--;
		}
	}
	void deleteBack() {
		if(length() == 1) {
			clear();
		}
		else if(length() >1) {
			if(cursor == back) {
				cursor = null;
				indexcursor = -1;
			}
			back = back.previous;
			back.next = null;
			length--;
		}
		else if (length() == 0) {
			throw new RuntimeException("Cannot delete from an empty list");
		}
	}
	void delete() {
		if(cursor == null) {
			throw new RuntimeException("Cannot delete a non-existing cursor");
		}
		if(length() <= 0) {
			throw new RuntimeException("Cannot delete from an empty list");
		}
		if(length() > 0 && indexcursor >= 0) {
			if(cursor.previous != null && cursor.next != null) {
				cursor.previous.next = null;
				cursor.next.previous = null;
				cursor = null;
				indexcursor = -1;
			}
			else if(cursor.previous == null) {
				front = cursor.next;
				if(cursor.next != null) {
					front.previous = null;
				}
				cursor = null;
				indexcursor = -1;
			}
			else if(cursor.next == null) {
				back = cursor.previous;
				back.next = null;
				cursor = null;
				indexcursor = -1;
			}
		}
		length--;
	}
	public String toString() {
		String s = "";
		if(length() != 0) {
			Node N = front;
			while(N != null) {
				if(N.next != null) {
					s = s + String.valueOf(N.value) + " ";
				}
				else {
					s = s + String.valueOf(N.value);
				}
				N = N.next;

			}
		}
		return s;
	}
}

