import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


public class length {

	public static void main(String[] args) {
		readFile();
		for(int j=0;j<9;j++){
			result[j]=toMeter(data[j]);
			if(j>5){
				result[j]=operate(data[j]);
			}
			System.out.println("result "+result[j]);
		}
		writeFile();
	}
	
	public static double todouble(String s){
		return  Double.parseDouble(s);
	}
	
	public static double getNum(String num){
		return todouble(num.substring(0,num.indexOf(" ")));
	}
	
	public static String getUnit(String str){
		return str.substring(str.indexOf(" ")+1);
	}
	
	public static double toMeter(String str){
		if(getUnit(str).equals("miles")){		return getNum(str) * todouble(myMap.get("mile"));	}
		if(getUnit(str).equals("yard")){		return getNum(str) * todouble(myMap.get("yard"));  	} 
		if(getUnit(str).equals("inches")){		return getNum(str) * todouble(myMap.get("inch"));  	} 
		if(getUnit(str).equals("feet")){		return getNum(str) * todouble(myMap.get("foot"));  	} 
		if(getUnit(str).equals("faths")){		return getNum(str) * todouble(myMap.get("fath"));  	} 
		if(getUnit(str).equals("furlong")){	return getNum(str) * todouble(myMap.get("furlong"));   } 
		return 0.0;
	}
	
	public static double operate(String str){
		int t=0;
		double re=0.0;
		while(str!=null){
			if(str.indexOf("+")!=-1){
				re=+toMeter(str.substring(0, str.indexOf("+")-1));
				str=str.substring(str.indexOf("+")+1);
			}else if(str.indexOf("-")!=-1){
				re=-toMeter(str.substring(0, str.indexOf("-")-1));
				str=str.substring(str.indexOf("-")+1);
			}else{
				str=null;
			}
		}
		return re;
	} 
	
	public static void readFile(){
		File file=new File("input.txt");
		
		if(!file.exists()){ System.out.println("no file"); return; }
	
		try {
            BufferedReader in = new BufferedReader(new FileReader(file));
            int i=0;
            while ((str = in.readLine()) != null) {
                if((temp++)<6){
                	myMap.put(str.substring(2,str.indexOf("=")-1),str.substring(str.indexOf("=")+2,str.length()-2));
                	
                }else if(str.length()!=0){
                	data[i++]=str;
				}       	
            }
            in.close();
        }catch (IOException e) {
            e.getStackTrace();
        }
	}

	public static void writeFile(){
		File file=new File("output.txt");
		
		if(!file.exists()){ System.out.println("no write file"); return; }
		
		try {
            BufferedWriter out = new BufferedWriter(new FileWriter(file));

            out.write("w812609862@gmail.com");
            out.newLine();
            
            for(int n=0;n<10;n++){
            	out.write(new java.text.DecimalFormat("#.00").format(result[n]));
            }
            out.close();
        }catch (IOException e) {
            e.getStackTrace();
        }
	}
	private static Map<String, String> myMap=new HashMap();
	private static int temp;
	private static String str;
	private static String[] data=new String[10];
	private static double result[]=new double[10];
	
}
