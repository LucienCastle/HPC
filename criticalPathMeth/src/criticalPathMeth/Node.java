package criticalPathMeth;

public class Node {
	int id;
	int distance;
	Node(int id, int distance) {
		this.id = id;
		this.distance = distance;
	}
	public int getId() {
	 	return id;
	}
	public void setId(int id) {
	 	this.id = id;
	}
	public int getdistance() {
	 	return distance;
	}
	public void setdistance(int distance) {
		this.distance = distance;
	}
}
