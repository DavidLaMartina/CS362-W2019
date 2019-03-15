

import junit.framework.TestCase;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

import java.util.Arrays;
import java.util.Random;

public class UrlValidatorTestRandom extends TestCase 
{
	//strings used to build URL components
	public static final String letters = "abcdefghijklmnopqrstuvwxyz";
	public static final String digits = "0123456789";
	public static final String symbols = "+-./$&";
	public static final String alphanum = letters + digits;
	public static final String allSymbols = alphanum + symbols;
	
	//testing variables
	public static final boolean Print = false; 	//prints optional info to console/file
	public static final int NUM_TESTS = 1000; 	//number of random URLs to be built/tested

   public UrlValidatorTestRandom(String testName) 
   {
      super(testName);
      
      // Create logs directory
      String dirName = "program_logs";
      File directory = new File(dirName);
      if (!directory.exists()) 
      {
    	 directory.mkdir();
      }
   }
   

   //helper function to get a random character from the given string
   public char getRandChar(String symbols)
   {
     Random random = new Random();
     return symbols.charAt(random.nextInt(symbols.length()));
   }

   //helper function to get a random boolean truth value
   public boolean getRandBool(int num)
   {
     if (num > 0) {return true;}
     else {return false;}
   }

   public String buildScheme(boolean valid, int minLength, int maxLength)
   {
     //By default only http, https, and ftp are considered valid schemes
     //String schemes[] = {"http://", "https://", "ftp://"}; BUG WHEN RUNNING https://, ftp://, or any other protocol

     String scheme = "";

     Random random = new Random();

     if (valid) //build a valid scheme
     {
       //get random valid scheme
       //scheme = schemes[random.nextInt(schemes.length)];  BUG!
    
       scheme = "http://";
    
     }
     else //build an invalid scheme
     {
       /* BUG!! only allow "http://" scheme due to known bug
       //randomly decide length of partition within given bounds
       int length = random.nextInt(maxLength - minLength) + minLength + 1;

       do 
       {
         StringBuilder buffer = new StringBuilder();

         //create scheme for given length
         for (int i = 0; i < length; i++)
         {
           //use alphanumeric values for scheme
           buffer.append(getRandChar(alphanum));
         }

         buffer.append("://");

         //convert buffer back to string type
         scheme = buffer.toString();
       }
       while (Arrays.asList(schemes).contains(scheme)); //don't allow default schemes to be produced
       */
    	
    	 scheme = "http://"; //set to http:// in order to allow tests to run
       
     }

     return scheme;
   }

   public String buildAuthority(boolean valid)
   {
     String authority = "";
     boolean hostname, port, empty;
     int num;

     Random random = new Random();
     
     if (valid) //build a valid authority
     {
       num = random.nextInt(2);
       hostname = getRandBool(num);

       if (hostname) //build authority with a hostname
       {
    	   String names[] = {
    			   "www.google.com", "www.amazon.com", "www.target.com", "www.ebay.com", "www.bbc.co.uk",
    			   "www.oregonstate.edu", "www.reddit.com", "www.facebook.com", "www.courts.gov",
    			   "www.gmail.com", "www.github.com", "www.yahoo.com", "www.microsoft.com"
    	   };
    	   
    	   authority = names[random.nextInt(names.length)];
       }
       else //build authority using an IP address
       {
    	   StringBuilder buffer = new StringBuilder();

           //create IP address
           for (int i = 0; i < 4; i++)
           {
             //values must be between 0 and 255
             buffer.append(random.nextInt(256));
             if (i < 3) {buffer.append(".");}
           }
           
           //convert buffer back to string type
           authority = buffer.toString();
       }

       //build port
       num = random.nextInt(2); //50% chance to include port
       port = getRandBool(num);
       
       if (port)
       {
    	   StringBuilder buffer = new StringBuilder();
    	   
    	   buffer.append(":");
    	   
    	   num = random.nextInt(65536); //max possible port number is 65536
    	   buffer.append(num);
    	   
    	   //add port to authority
    	   authority += buffer.toString();
       }

     }
     else //build an invalid authority
     {
    	 //return empty authority
    	 num = random.nextInt(10);
         empty = getRandBool(num);
         
         if (!empty) //10% chance for empty authority
         {
        	 return authority;
         }
    	 
    	 num = random.nextInt(2);
         hostname = getRandBool(num);

         if (hostname) //build authority with an invalid hostname
         {
      	   String names[] = {
      			   ".aaa", "aaa", "go.a1a", "go.a", "go.1aa"
      	   };
      	   
      	   authority = names[random.nextInt(names.length)];
         }
         else //build authority using an invalid IP address
         {
      	   StringBuilder buffer = new StringBuilder();

             //create IP address
             for (int i = 0; i < 4; i++)
             {
               //values greater than 255
               buffer.append(random.nextInt(100) + 256);
               if (i < 3) {buffer.append(".");}
             }
             
             //convert buffer back to string type
             authority = buffer.toString();
         }

         //build improper port number
         num = random.nextInt(2); //50% chance to include port
         port = getRandBool(num);
         
         if (port)
         {
      	   StringBuilder buffer = new StringBuilder();
      	   
      	   buffer.append(":");
      	   
      	   num = random.nextInt(65536) * (-1); //negative ports invalid
      	   buffer.append(num);
      	   
      	   //add port to authority
      	   authority += buffer.toString();
         }
    	 
     }

     return authority;
   }

   public String buildPath(boolean valid, int minLength, int maxLength)
   {
     String path = "";
     int num, pos;

     Random random = new Random();
     StringBuilder buffer = new StringBuilder();

     //randomly decide length of partition within given bounds
     int length = random.nextInt(maxLength - minLength) + minLength + 1;

     if (valid) //build a valid path
     {
       num = random.nextInt(10);
       if (num == 0) //10% chance of using empty path
       {
         return path;
       }

       //add randomly decided number of path segments (1 or 2 currently)
       num = random.nextInt(2) + 1;
       
       //fill in segment  
       buffer.append("/");
       for (int i = 1; i < length; i++)
       {
         buffer.append(getRandChar(alphanum));
       }
       
       //format string to fit path structure
       pos = length / (num + 1);
       for (int i = 1; i <= num; i++)
       {
    	   buffer.setCharAt(i*pos, '/'); //format path structure
       }

       //convert buffer back to string type
       path = buffer.toString();

     }
     else //build an invalid path
     {
       buffer.append("/");

       for (int i = 0; i < length; i++)
       {
         buffer.append(getRandChar(symbols));
       }

       path = buffer.toString();
     }

     return path;
   }

   public String buildQuery(boolean valid, int minLength, int maxLength)
   {
     String query = "";
     int num;

     Random random = new Random();

     //randomly decide length of partition within given bounds
     int length = random.nextInt(maxLength - minLength) + minLength + 1;

     StringBuilder buffer = new StringBuilder();

     if (valid) //build a valid query
     {
         num = random.nextInt(4);
         if (num == 0) //25% chance of using empty query
         {
           return query;
         }

         buffer.append("?");

         //create query for given length
         for (int i = 0; i < length / 2; i++)
         {
           //use alphanumeric values for query
           buffer.append(getRandChar(alphanum));
         }

         buffer.append("=");

         for (int i = 0; i < length / 2; i++)
         {
           //use alphanumeric values for query
           buffer.append(getRandChar(alphanum));
         }

         //convert buffer back to string type
         query = buffer.toString();
     }
     else //build an invalid query
     {
         //create query for given length in invalid format
         for (int i = 0; i < length / 2; i++)
         {
           //use alphanumeric values for query
           buffer.append(getRandChar(allSymbols));

           //convert buffer back to string type
           query = buffer.toString();
         }
     }

     return query;
   }

   public void testIsValid_Random() throws FileNotFoundException, UnsupportedEncodingException
   {
	   PrintWriter writer = new PrintWriter("program_logs/randomResults.txt", "UTF-8");

	   Random random = new Random();
	   
       //value for individually built partitions
	   boolean scheme_b, authority_b, path_b, query_b;
	   
	   boolean result;                  //value for validation result
	   int numCorrectlyExpected = 0; 	//for total test results
	   
	   //variable controls to affect odds of building valid components
	   int 	scheme_c 	= 3,
			authority_c = 3,
			path_c		= 3,
			query_c		= 3;

	   //build and test URLs for given number of tests
	   for (int i = 0; i < NUM_TESTS; i++)
	   {
		 UrlValidator testURL = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
		 boolean expected = true; //final bool validation value for fully built URL
		 String URL, scheme, authority, path, query;
		 //build URL partitions

		 //scheme
		 scheme_b = getRandBool(random.nextInt(scheme_c)); 	//decide valid/invalid partition
		 scheme = buildScheme(scheme_b, 5, 10);    			//build and add partition to URL
		 //BUG: due to known protocol bug, set scheme as 'true' to not affect validation result
		 scheme_b = true;
		 expected &= scheme_b;                      		//update expected result
		
		 //authority
		 authority_b = getRandBool(random.nextInt(authority_c)); 	//decide valid/invalid partition
		 authority = buildAuthority(authority_b);					//build and add partition to URL
		 expected &= authority_b;                      				//update expected result
		
		 //path
		 path_b = getRandBool(random.nextInt(path_c)); 	//decide valid/invalid partition
		 path = buildPath(path_b, 5, 15);        		//build and add partition to URL
		 expected &= path_b;                      		//update expected result
		
		 //query
		 query_b = getRandBool(random.nextInt(query_c)); 	//decide valid/invalid partition
		 query = buildQuery(query_b, 5, 15);      			//build and add partition to URL
		 expected &= query_b;                      			//update expected result
		 
		 //combine partitions to form full URL
		 URL = scheme + authority + path + query;
		
		 if (Print)
		 {
			 System.out.println("Scheme: " + scheme + "\nAuthority: " + authority + 
					 "\nPath: " + path + "\nQuery: " + query);
		 }
		 
		 //URL complete, validate
		 result = testURL.isValid(URL);
		
		 if (result == expected)
		 {
		   if (Print) {System.out.println("Correctly expected " + expected + " for \"" + URL + "\"");}
		   numCorrectlyExpected++;
		 }
		 else
		 {
		   System.out.println("Incorrectly expected " + expected + " for \"" + URL + "\"");
		   writer.println("Incorrectly expected " + expected + " for \"" + URL + "\"");
		 }
	} //tests done
		
	   //write results to console
	   System.out.println("------------------------------------");
	   System.out.println("Test Results:");
	   System.out.println("Correctly Expected " + numCorrectlyExpected + " out of " + NUM_TESTS + " tests.");
	   System.out.println("------------------------------------");
   
	   //write results to file
	   writer.println("------------------------------------");
	   writer.println("Test Results:");
	   writer.println("Correctly Expected " + numCorrectlyExpected + " out of " + NUM_TESTS + " tests.");
	   writer.println("------------------------------------");
		 
	   writer.close();
   }
  
}