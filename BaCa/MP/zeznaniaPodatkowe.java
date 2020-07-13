// Lukasiewicz Jakub - 3
import java.util.Scanner;
class Source {
	static Scanner I=new Scanner(System.in);
	static int s(int[] T,int A,int x,int L,int R) { //binSearch
		int l=0,r=A-1,p=-1;
		if(T[r]<x) return r;
		if(T[l]>x) return l;
		while(l<=r) {
			int m=(l+r)>>>1;
			if(T[m]<x){
				l=m+1;
			}else if(T[m]>x){
				r=m-1;
			}else{
				p=m;
				r=L>0?m-1:r;
				l=R>0?m+1:l;
			}
		}
		return p<0?r+L:p;
	}
	public static void main(String[] args) {
		int E,n,A,B,x,y,u,z,q;
		E=I.nextInt();
		for(int e=0;e<E;e++){
			u=1;
			A=I.nextInt();
			int[] t=new int[A];
			for(int a=0;a<A;a++){
				t[a]=I.nextInt();
				if(a>0&&t[a]>t[a-1]) u++;
			}
			B=I.nextInt();
			for(int b=0;b<B;b++){
				z=0;q=0;
				x=I.nextInt();
				y=I.nextInt();
				if(t[A-1]>=x && t[0]<=y){
					q=s(t,A,x,1,0);
					z=s(t,A,y,0,1);
					z=q>0?z-q:z;
					z=z<0?0:z+1;
				}
				System.out.println(z);
			}
			System.out.println(u);
		}
	}
}
