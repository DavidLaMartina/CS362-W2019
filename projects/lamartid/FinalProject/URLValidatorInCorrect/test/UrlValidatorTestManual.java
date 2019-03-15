

import junit.framework.TestCase;

import java.net.IDN;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Scanner;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTestManual extends TestCase {


   public UrlValidatorTestManual(String testName) {
      super(testName);
   }

   public void runDefault(String url) {
	   
	   // default constructor
	   UrlValidator urlValidator = new UrlValidator();
	   try {
		   if (urlValidator.isValid(url)) {
			      System.out.println(url + " is valid");
			   } else {
			    System.out.println(url + " is invalid");
			   }
	   }
	   catch (Error e) {
		   System.out.println("Error caught: " + e);
	   }
   }
   
public void runTwoSchemes(String url) {
	   
	   // allow http and https schemes
		String[] schemes = {"http","https"};
	   UrlValidator urlValidator = new UrlValidator(schemes);
	   try {
		   if (urlValidator.isValid(url)) {
			      System.out.println(url + " is valid");
			   } else {
			    System.out.println(url + " is invalid");
			   }
	   }
	   catch (Error e) {
		   System.out.println("Error caught: " + e);
	   }
   }
   
   
		   
public void runAnyScheme(String url) {
	   
	   // allow any scheme
	long options = UrlValidator.ALLOW_ALL_SCHEMES;
	   
	UrlValidator urlValidator = new UrlValidator(options);
	   
	  try {
		   if (urlValidator.isValid(url)) {
			      System.out.println(url + " is valid");
			   } else {
			    System.out.println(url + " is invalid");
			   }
		  }
	  catch (Error e) {
		  System.out.println("Error caught: " + e);
	  }
}

public void runTwoSlashes(String url) {
	   
	   // allow 2 slashes
	long options = UrlValidator.ALLOW_2_SLASHES
			+ UrlValidator.ALLOW_ALL_SCHEMES;
	   
	UrlValidator urlValidator = new UrlValidator(options);
	   
	  try {
		   if (urlValidator.isValid(url)) {
			      System.out.println(url + " is valid");
			   } else {
			    System.out.println(url + " is invalid");
			   }
		  }
	  catch (Error e) {
		  System.out.println("Error caught: " + e);
	  }
}

public void runNoFragments(String url) {
	   
	   // no fragments
	long options = UrlValidator.NO_FRAGMENTS
			+ UrlValidator.ALLOW_ALL_SCHEMES;
	   
	UrlValidator urlValidator = new UrlValidator(options);
	   
	  try {
		   if (urlValidator.isValid(url)) {
			      System.out.println(url + " is valid");
			   } else {
			    System.out.println(url + " is invalid");
			   }
		  }
	  catch (Error e) {
		  System.out.println("Error caught: " + e);
	  }
}
   
public void runLocalUrls(String url) {
	   
	   // allow local urls
	long options = UrlValidator.ALLOW_LOCAL_URLS
			+ UrlValidator.ALLOW_ALL_SCHEMES;
	   
	UrlValidator urlValidator = new UrlValidator(options);
	   
	  try {
		   if (urlValidator.isValid(url)) {
			      System.out.println(url + " is valid");
			   } else {
			    System.out.println(url + " is invalid");
			   }
		  }
	  catch (Error e) {
		  System.out.println("Error caught: " + e);
	  }
}

 //You can use this function to implement your manual testing
   public void testManualTest()
   {
	  
		Scanner myObj = new Scanner(System.in);
		String url;
		String s;
		String flag = "run";
		String choice;
		
		System.out.println("1. Run Tests with Default Constructor >>");
		System.out.println("2. Run Tests with 2 schemes http and https >>");
		System.out.println("3. Run Tests with any scheme >>");
		System.out.println("4. Run Tests allowing 2 slashes >>");
		System.out.println("5. Run Tests not allowing fragments >>");
		System.out.println("6. Run Tests allowing local urls >>");
		
		System.out.println("Enter your choice >>");
		choice = myObj.nextLine();
		
		while (flag == "run")
		{
			System.out.println("Enter url or type quit to end session >>");
			s = myObj.nextLine();
			if (s.equalsIgnoreCase("quit"))
			{
				flag = s;
			}
			else
			{
				if (choice.equals("1"))
				{
					runDefault(s);
				}
				else if (choice.equals("2"))
				{
					runTwoSchemes(s);
				}
				else if (choice.equals("3"))
				{
					runAnyScheme(s);
				}
				else if (choice.equals("4"))
				{
					runTwoSlashes(s);
				}
				else if (choice.equals("5"))
				{
					runNoFragments(s);
				}
				else if (choice.equals("6"))
				{
					runLocalUrls(s);
				}
				else
				{
					System.out.println("Invalid Choice >>");
				}
					 
			}
			
		}
	   
		System.out.println("Your session has ended");
   }
   
   
  
public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
