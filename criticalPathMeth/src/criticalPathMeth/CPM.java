package criticalPathMeth;
import java.util.*;

public class CPM {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		 GraphNet graph = new GraphNet(11);
		 graph.addEdge(1, 2, 10);
		 graph.addEdge(1, 3, 8);
		 graph.addEdge(1, 4, 9);
		 graph.addEdge(2, 5, 8);
		 graph.addEdge(3, 7, 16);
		 graph.addEdge(4, 6, 7);
		 graph.addEdge(5, 7, 7);
		 graph.addEdge(6, 7, 7);
		 graph.addEdge(5, 8, 6);
		 graph.addEdge(7, 10, 12);
		 graph.addEdge(6, 9, 5);
		 graph.addEdge(8, 10, 13);
		 graph.addEdge(9, 10, 15);
		 graph.printGraph();
		 graph.calculateEarlyStart();
		 graph.backPath();
		 System.out.println("\nCritical Path");
		 graph.criticalPath();
	}
}