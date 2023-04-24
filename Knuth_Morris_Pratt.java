package ALGO;

import java.util.*;
public class Knuth_Morris_Pratt {

	public static void main(String[] args) {
		Scanner sc= new Scanner(System.in); 
		String text= sc.nextLine(),pattern=sc.nextLine();
		for(var s:get_all_matches_of_p_in_s(text,pattern))
			System.out.println(s);
		sc.close();
	}
	 public static Set<Integer> get_all_matches_of_p_in_s(String s, String p) {
	        int n=s.length();
	        int[] lps=getLPS_table(p);
	        int a=0,b=0;	       
	        Set<Integer> ans=new TreeSet<>();
	        while(a<n){
	            if(s.charAt(a)==p.charAt(b)){
	                a++;
	                b++;
	                if(b==p.length()) {
	                    ans.add(a-b);
	                    b=0;
	                }
	            }
	            else{
	                if(b==0)
	                    a++;
	                else
	                    b=lps[b-1];
	            }
	        }
	        return ans;
	    }
	    static int[] getLPS_table(String s){
	        int n=s.length();
	        int[] lps=new int[n];
	        lps[0]=0;
	        for(int i=1;i<n;i++){
	            int j=lps[i-1];
	            while(j>0&&s.charAt(i)!=s.charAt(j))
	                j=lps[j-1];
	            if(s.charAt(j)==s.charAt(i))
	                lps[i]=j+1;
	            else 
	                lps[i]=0;
	        }
	        return lps;
	    }
}
