

import junit.framework.TestCase;

import java.io.FileNotFoundException;
import java.io.PrintWriter;


//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTestProgrammatic extends TestCase {


   public UrlValidatorTestProgrammatic(String testName) {
      super(testName);
   }
   
   public void testIsValidCombosValid()
   {
	   try {
		PrintWriter outputStream = new PrintWriter("../logs/test.txt");
		outputStream.println("In the file");
	} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   
	   String scheme = "http://";		// We've determined that only the http:// scheme avoids errors and crashes in the current code
	   String[] authorities = {
			   "www.google.com",
			   "www.yahoo.com",
			   "www.bing.com",
			   "www.alexa.com",
	   };
	   String[] ports = {
			   ":80",
			   ":3000",
			   ":65535", // should be max possible port
			   ":0"
	   };
	   String[] paths = {
			   "/test",
			   "/123",
			   "/test1/test2",
			   "/thing1/thing2/thing3"
	   };
	   String[] queries = {
			   "?action=view",
			   "?search=false",
			   "?req1=val1",
			   "?req1=val1&req2=val2"
	   };
	   for (String auth : authorities) {
		   // Build all possible strings, given set of orders
		   testURL = scheme + auth;
		   runIsValid(testURL, urlVal);
		   for (String port : ports) {
			   testURL= scheme + auth + port;
			   runIsValid(testURL, urlVal);
			   for (String query : queries) {
				   testURL = scheme + auth + port + query;
				   runIsValid(testURL, urlVal);
			   }
			   for (String path : paths) {
				   testURL = scheme + auth + port + path;
				   runIsValid(testURL, urlVal);
				   for (String query : queries) {
					   testURL = scheme + auth + port + path + query;
					   runIsValid(testURL, urlVal);
				   }
			   }
		   }
		   for (String path : paths) {
			   testURL = scheme + auth + path;
			   runIsValid(testURL, urlVal);
			   for (String query : queries) {
				   testURL = scheme + auth + path + query;
				   runIsValid(testURL, urlVal);
			   }
		   }
		   for (String query : queries) {
			   testURL = scheme + auth + query;
			   runIsValid(testURL, urlVal);
		   }
	   }
   }
   public void testIsValidCombosInvalid() {
	   String scheme = "http://";
	   String[] authorities = {
			   "go.a" // invalid top-level domain
	   };
	   String[] ports = {
			   ":65536"	// should be too large
	   };
   }
   public static void runIsValid(String testURL, UrlValidator urlVal) {
	   boolean validURL = urlVal.isValid(testURL);
	   if (!validURL) System.out.println(testURL);
   }
}