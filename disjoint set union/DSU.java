import java.io.*;
import java.util.*;

public class DSU{
        private int count;
        private int[] size,parent;
        public DSU(int size){
            this.size=new int[size];
            parent= new int[size];
            for(int i=0;i<size;i++)
                parent[i]=i;
            count=size;
        }
        public int find(int a){
            if(parent[a]==a)
                return a;
            return parent[a]=find(parent[a]);
        }
        public void union(int a,int b){
            int p1=find(a);
            int p2=find(b);
            if(p1==p2)
                return;
            if(size[p2]<size[p1]){
                int x=p1;
                p1=p2;
                p2=x;
            }
            parent[p1]=p2;
            size[p2]+=size[p1];
            count--;
        }
        public int getCount(){
            return  count;
        } 
    }
