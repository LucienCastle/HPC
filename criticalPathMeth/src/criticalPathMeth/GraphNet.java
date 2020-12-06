package criticalPathMeth;

import java.util.ArrayList;
import java.util.Iterator;
import criticalPathMeth.Node;


public class GraphNet {
	int length;
	ArrayList<Node> adjList[];
	int earlyStart[];
	int latestCompletion[];
	int visited[];
	GraphNet(int length) {
		this.length = length;
		adjList = new ArrayList[length];
		for (int i = 0; i < length; i++) {
			adjList[i] = new ArrayList<Node>();
		 }
		 visited = new int[length];
		 earlyStart = new int[length];
		 latestCompletion = new int[length];
		 for (int i = 0; i < length; i++) {
			 visited[i] = 0;
			 earlyStart[i] = 0;
			 latestCompletion[i] = 100;
		 }
	}
	public void addEdge(int tail, int head, int distance) {
		Node new2 = new Node(head, distance);
		adjList[tail].add(new2);
	}
	public void printGraph() {
		for (int i = 1; i < length; i++) {
			Iterator<Node> it = adjList[i].iterator();
			while (it.hasNext()) {
				Node n = (Node) it.next();
				int j = n.getId();
				int dist = n.getdistance();
				System.out.println(i + "-" + j + " " + dist);
			}
		}
	}
	public void calculateEarlyStart() {
		earlyStart[1] = 0;
		for (int i = 1; i < length; i++) {
			Iterator it = adjList[i].iterator();
			while (it.hasNext()) {
				Node n = (Node) it.next();
				int vertex = n.getId();
				int dist = n.getdistance();
				dist += earlyStart[i];
				if (earlyStart[vertex] < dist) {
						 earlyStart[vertex] = dist;
		 			}	
		 		}
		}
		System.out.println("\nEarly Start");
		for (int i = 1; i < length; i++) {
			System.out.println(i + " " + earlyStart[i]);
		}
	}
	public void backPath() {
		 ArrayList<Node> backList[];
		 backList = new ArrayList[length];
		 for (int i = 0; i < length; i++) {
			 backList[i] = new ArrayList<Node>();
		 }
		for (int i = 1; i < length; i++) {
			Iterator it = adjList[i].iterator();
			while (it.hasNext()) {
				Node n = (Node) it.next();
				int vertex = n.getId();
				int dist = n.getdistance();
				Node new1 = new Node(i, dist);
				backList[vertex].add(new1);
			}
		}
		latestCompletion[length - 1] = earlyStart[length - 1];
		for (int i = length - 1; i >= 0; i--) {
			Iterator it = backList[i].iterator();
			while (it.hasNext()) {
				Node n = (Node) it.next();
				int vertex = n.getId();
				int dist = n.getdistance();
				int dist1 = latestCompletion[i] - dist;
				if (latestCompletion[vertex] > dist1) {
					latestCompletion[vertex] = dist1;
				}
			}
		}
		System.out.println("\nLatest Completion");
		for (int i = 1; i < length; i++) {
			System.out.println(i + " " + latestCompletion[i]);
		}
	}
	public void criticalPath() {
		boolean path[] = new boolean[length];
		int crit[] = new int[length];
		path[1] = true;
		crit[1] = 1;
		for (int i = 2; i < length; i++){
			path[i] = false;
			crit[i] = 0;
		}
		int idx = 1;
		for (int i = 1; i < length; i++) {
			if (earlyStart[i] == latestCompletion[i]) {
				Iterator it = adjList[crit[idx-1]].iterator();
				while (it.hasNext()) {
					Node n = (Node) it.next();
					int vertex = n.getId();
					if (i == vertex) {
						path[i] = true;
						crit[idx] = i;
					}
			 	}
				if (i == length - 1) {
					if(path[i] == true){
						System.out.print(i + " ");
						idx++;
					}
				} else {
					if(path[i] == true){
						System.out.print(i + "->");
						idx++;
					}
				}
			}
		}
	}
}
