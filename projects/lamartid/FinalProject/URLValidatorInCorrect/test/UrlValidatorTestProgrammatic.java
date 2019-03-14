

import junit.framework.TestCase;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

public class UrlValidatorTestProgrammatic extends TestCase {


   public UrlValidatorTestProgrammatic(String testName) {
      super(testName);
      
      // Create logs directory
      String dirName = "program_logs";
      File directory = new File(dirName);
      if (!directory.exists()) {
    	  directory.mkdir();
      }
   }
   
   public void testIsValidCombosValid() throws FileNotFoundException, UnsupportedEncodingException
   {
	   PrintWriter writer = new PrintWriter("program_logs/CombosValid.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   
	   String scheme = "http://";		// We've determined that only the http:// scheme avoids errors and crashes in the current code
	   String[] authorities = {
			   "www.google.com",
			   "www.yahoo.com",
			   "www.bing.com",
			   "www.alexa.com",
			   "12.34.35.6"
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
	   writer.println("Testing valid URLs of various combinations...");
	   writer.println("URLs incorrectly flagged as invalid:");
	   for (String auth : authorities) {
		   // Build all possible strings, given set of orders
		   testURL = scheme + auth;
		   runIsValid(testURL, urlVal, writer);
		   for (String port : ports) {
			   testURL= scheme + auth + port;
			   runIsValid(testURL, urlVal, writer);
			   for (String query : queries) {
				   testURL = scheme + auth + port + query;
				   runIsValid(testURL, urlVal, writer);
			   }
			   for (String path : paths) {
				   testURL = scheme + auth + port + path;
				   runIsValid(testURL, urlVal, writer);
				   for (String query : queries) {
					   testURL = scheme + auth + port + path + query;
					   runIsValid(testURL, urlVal, writer);
				   }
			   }
		   }
		   for (String path : paths) {
			   testURL = scheme + auth + path;
			   runIsValid(testURL, urlVal, writer);
			   for (String query : queries) {
				   testURL = scheme + auth + path + query;
				   runIsValid(testURL, urlVal, writer);
			   }
		   }
		   for (String query : queries) {
			   testURL = scheme + auth + query;
			   runIsValid(testURL, urlVal, writer);
		   }
	   }
	   writer.close();
   }
   public void testIsValidCombosInvalid() throws FileNotFoundException, UnsupportedEncodingException {
	   PrintWriter writer = new PrintWriter("program_logs/CombosInvalid.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   
	   String scheme = "http://";		// We've determined that only the http:// scheme avoids errors and crashes in the current code
	   String[] authorities = {
			   "www.go.a",
			   "aaa.",
			   "",
			   ".1.2.3",
	   };
	   String[] ports = {
			   ":-1",
			   ":65536",
			   ":123123123", // should be max possible port
			   ":45l"
	   };
	   String[] paths = {
			   "/..//..",
			   "/try//this",
			   "/#/file",
			   "/../"
	   };
	   String[] queries = {
			   "??",
			   "09p",
			   "aquery",
			   "query?"
	   };
	   writer.println("Testing invalid URLs of various combinations...");
	   writer.println("URLs incorrectly flagged as valid:");
	   for (String auth : authorities) {
		   // Build all possible strings, given set of orders
		   testURL = scheme + auth;
		   runIsInvalid(testURL, urlVal, writer);
		   for (String port : ports) {
			   testURL= scheme + auth + port;
			   runIsInvalid(testURL, urlVal, writer);
			   for (String query : queries) {
				   testURL = scheme + auth + port + query;
				   runIsInvalid(testURL, urlVal, writer);
			   }
			   for (String path : paths) {
				   testURL = scheme + auth + port + path;
				   runIsInvalid(testURL, urlVal, writer);
				   for (String query : queries) {
					   testURL = scheme + auth + port + path + query;
					   runIsInvalid(testURL, urlVal, writer);
				   }
			   }
		   }
		   for (String path : paths) {
			   testURL = scheme + auth + path;
			   runIsInvalid(testURL, urlVal, writer);
			   for (String query : queries) {
				   testURL = scheme + auth + path + query;
				   runIsInvalid(testURL, urlVal, writer);
			   }
		   }
		   for (String query : queries) {
			   testURL = scheme + auth + query;
			   runIsInvalid(testURL, urlVal, writer);
		   }
	   }
	   writer.close();
   }
   public void testIsValidAuth() throws FileNotFoundException, UnsupportedEncodingException {
	   /*
	    * Test various authorities / domains, using set of characters and lengths
	    */
	   PrintWriter writer = new PrintWriter("program_logs/auth.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   String firstPart;
	   String[] authorities = {"google.com", "bing.com", "alexa.com", "yahoo.com"};
	   for (String auth : authorities) {
		   testURL = "http://" + auth;
		   runIsValid(testURL, urlVal, writer);
		   testURL += "/dir";
		   runIsValid(testURL, urlVal, writer);
	   }
	   
	   // Test authorities without www
	   writer.println("Testing VALID authorities without 'www' prefix (should be valid)");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   testURL = "http://google.com";
	   runIsValid(testURL, urlVal, writer);
	   
	   // Test authorities of various lengths - valid
	   writer.println("\nTesting VALID authorities of various lengths...");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   firstPart = "http://www.abc";
	   for (int i = 0; i < 100; i++) {
		   firstPart += "d";
		   testURL = firstPart + ".com";
		   runIsValid(testURL, urlVal, writer);
	   }
	   // Test authorities of various lengths - INvalid - 2 dots between scheme and domain name
	   writer.println("\nTesting INVALID authorities of various lengths - 2 dots between www and domain name");
	   writer.println("URLs incorrectly flagged as valid\n");
	   firstPart = "http://www..abc";
	   for (int i = 0; i < 100; i++) {
		   firstPart += "d";
		   testURL = firstPart = ".com";
		   runIsInvalid(testURL, urlVal, writer);
	   }
	   
	   // Test authorities of various lengths - INvalid - 2 dots between domain name and com
	   writer.println("\nTesting INVALID authorities of various lengths - 2 dots between domain name and com");
	   writer.println("URLs incorrectly flagged as valid\n");
	   firstPart = "http://www.abc..";
	   for (int i = 0; i < 100; i++) {
		   firstPart += "d";
		   testURL = firstPart + ".com";
		   runIsInvalid(testURL, urlVal, writer);
	   }
	   writer.close();
   }
   public void testIsValidNumericAuth() throws FileNotFoundException, UnsupportedEncodingException {
	   /*
	    * Test various IP addresses
	    */
	   
	   PrintWriter writer = new PrintWriter("program_logs/authNumeric.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   String firstPart;
	   
	   // Test valid ranges when there are 4 numbers
	   writer.println("Testing VALID IP addresses (4 dot-separated numbers, each [0-255]");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   firstPart = "http://";
	   for (int i = 0; i < 256; i += 20) {
		   for (int j = 0; j < 256; j += 20) {
			   for (int k = 0; k < 256; k += 20) {
				   for (int l = 0; l < 256; l += 20) {
					   testURL = firstPart + Integer.toString(i) +"." + Integer.toString(j) +
							   "." + Integer.toString(k) + "." + Integer.toString(l);
					   runIsValid(testURL, urlVal, writer);
				   }
			   }
		   }
	   }
	   // Test invalid ranges when there are 4 numbers
	   writer.println("Testing INVALID IP addresses (4 dot-separated numbers, 256+)");
	   writer.println("URLs incorrectly flagged as valid\n");
	   firstPart = "http://";
	   for (int i = 256; i < 512; i += 20) {
		   for (int j = 256; j < 512; j += 20) {
			   for (int k = 256; k < 512; k += 20) {
				   for (int l = 256; l < 512; l += 20) {
					   testURL = firstPart + Integer.toString(i) +"." + Integer.toString(j) +
							   "." + Integer.toString(k) + "." + Integer.toString(l);
					   runIsInvalid(testURL, urlVal, writer);
				   }
			   }
		   }
	   }
	   // Test invalid numbers of elements in IP address with correct ranges
	   writer.println("\nTest INVALID IP address with 1, 2, 3, and 5+ elements (wrong number of numbers)");
	   writer.println("URLs incorrectly flagged as valid\n");
	   testURL = "http://200";
	   for (int i = 0; i < 10; i++) {
		   if (i != 3) {
			   testURL += ".200";
			   runIsInvalid(testURL, urlVal, writer);
		   }
	   }
	   writer.close();
   }
   public void testIsValidPorts() throws FileNotFoundException, UnsupportedEncodingException {
	   /*
	    * Tests what ports (if any) can be added to valid scheme + authority
	    * Rationale: It seems no port can be added to still arrive at "valid" URL
	    * 
	    * Ports must be between 1 and 65535, inclusive
	    */
	   PrintWriter writer = new PrintWriter("program_logs/ports.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   
	   String first = "http://www.google.com";		// Scheme and authority known to be valid
	   
	   String path = "/testpath";					// known valid path
	   
	   String[] validPorts = {":0", ":36", ":234", "3456", "65535"};				// Test one port of each length
	   String[] invalidPorts = {":-1", ":abc", ":3000a", ":65536", ":999999999999"};		// various abnormalities
	   
	   // valid ports loop
	   writer.println("Testing valid ports by themselves...");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   testURL = first + ":" + Integer.toString(5);
	   runIsValid(testURL, urlVal, writer);
	   testURL = first + ":" + Integer.toString(55);
	   runIsValid(testURL, urlVal, writer);
	   for (int i = 0; i < 65536; i += 100) {
		   testURL = first + ":" + Integer.toString(i);
		   runIsValid(testURL, urlVal, writer);
	   }
	   writer.println("\nTesting valid ports with valid path...");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   for (int i = 0; i < 65536; i += 50) {
		   testURL = first + ":" + Integer.toString(i) + path;
		   runIsValid(testURL, urlVal, writer);
	   }
	   // invalid ports
	   writer.println("\nTesting invalid ports by themselves...");
	   writer.println("URLs incorrectly flagged as valid\n");
	   for (String port: invalidPorts) {
		   testURL = first + port;
		   runIsInvalid(testURL, urlVal, writer);
	   }
	   writer.println("/nTesting invalid ports with valid path");
	   writer.println("URLs incorrectly flagged as valid\n");
	   for (String port: invalidPorts) {
		   testURL = first + port + path;
		   runIsInvalid(testURL, urlVal, writer);
	   }
	   writer.close();
   }
   public void testIsValidPaths() throws FileNotFoundException, UnsupportedEncodingException {
	   /*
	    * Tests whether paths of various lengths (in terms of # of subdirectories) return appropriate results
	    * 
	    * Based on combos and ports tests, we know http://www.google.com, followed by either no port or a 4- or 5-
	    * digit port, should be valid
	    */
	   PrintWriter writer = new PrintWriter("program_logs/paths.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   
	   String[] validPaths = {
			  "/$25",
			  "/#asdf",
			  "/$df#",
			  "/#er/$45",
			  "/dir78/#yt/fg4",
			  "/#er/$45/#er/$45"
	   };
	   
	   String[] invalidPaths = {
			   "/#/file",
			   "/../../file",
			   "/dir//file",
			   "/../",
	   };
	   
	   String firstNoPort = "http://www.google.com";
	   String firstWithPort = "http://www.google.com:3000";
	   
	   // valid paths of varying lengths, both in terms of # subdirectories and length of terms
	   writer.println("Testing VALID paths of various lengths, without a port");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   for (int i = 0; i <= 5; i++) {
		   testURL = firstNoPort;
		   for (int j = 0; j <= i; j++) {
			   testURL += ("/dir" + Integer.toString(j));
		   }
		   runIsValid(testURL, urlVal, writer);
	   }
	   writer.println("\nTesting VALID paths of various lengths, with a port");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   for (int i = 0; i <= 5; i++) {
		   testURL = firstWithPort;
		   for (int j = 0; j <= i; j++) {
			   testURL += ("/dir" + Integer.toString(j));
		   }
		   runIsValid(testURL, urlVal, writer);
	   }
	   // valid 1-directory path of varying length
	   writer.println("\nTesting VALID 1-directory paths of various lengths, without a port");
	   writer.println("URLs incorrectly flagged as invalid");
	   testURL = firstNoPort + "/dir";
	   for (int i = 0; i < 10; i++) {
		   for (int j = 0; j < i; j++) {
			   testURL += "d";
		   }
		   runIsValid(testURL, urlVal, writer);
	   }
	   writer.println("\nTesting VALID 1-directory paths of various lengths, with a port");
	   writer.println("URLs incorrectly flagged as invalid");
	   testURL = firstNoPort + "/dir";
	   for (int i = 0; i < 10; i++) {
		   for (int j = 0; j < i; j++) {
			   testURL += "d";
		   }
		   runIsValid(testURL, urlVal, writer);
	   }
	   // valid paths with special traits or characters
	   writer.println("\nTesting VALID paths with special traits or characters");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   for (String path : validPaths) {
		   testURL = firstNoPort;
		   testURL += path;
		   runIsValid(testURL, urlVal, writer);
	   }
	   // invalid paths
	   writer.println("\nTesting INVALID paths with special traits or characters");
	   writer.println("URLs incorrectly flagged as valid\n");
	   for (String path : invalidPaths) {
		   testURL = firstNoPort;
		   testURL += path;
		   runIsInvalid(testURL, urlVal, writer);
	   }
	   writer.close();
   }
   
   public void testIsValidTLD() throws FileNotFoundException, UnsupportedEncodingException {
	   /*
	    * Test various top-level domains.
	    * If TLD is valid, so should be valid URLs using that TLD.
	    * If TLD is invalid, "" should not ""
	    */
	   
	   PrintWriter writer = new PrintWriter("program_logs/TLD.txt", "UTF-8");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL;
	   String first = "http://www.google.";		// Known to be valid until this point
	   
	   String[] validTLDs = {"com", "org", "net", "co", "rus", "au", "ca", "jp"};
	   String[] invalidTLDs = {"laa", "3rt4", "ala", "123", "34544"};
	   
	   // valid TLDs
	   writer.println("Testing VALID top-level domains with known valid first portion of URL");
	   writer.println("URLs incorrectly flagged as invalid\n");
	   for (String TLD : validTLDs) {	   
		   for (int i = 0; i < 5; i++) {
			   testURL = first + TLD;
			   for (int j = 0; j < i; j++) {
				   testURL += "/dir";
			   }
			   runIsValid(testURL, urlVal, writer);
		   }
	   }
	   // Invalid TLDs
	   writer.println("\nTesting INVALID top-level domains with known valid first portion of URL");
	   writer.println("URLs incorrectly flagged as valid\n");
	   for (String TLD : invalidTLDs) {	   
		   for (int i = 0; i < 5; i++) {
			   testURL = first + TLD;
			   for (int j = 0; j < i; j++) {
				   testURL += "/dir";
			   }
			   runIsInvalid(testURL, urlVal, writer);
		   }
	   }
	   writer.close();
   }
   
   public static void runIsValid(String testURL, UrlValidator urlVal, PrintWriter writer) {
	   boolean validURL = urlVal.isValid(testURL);
	   if (!validURL) writer.println(testURL);
   }
   public static void runIsInvalid(String testURL, UrlValidator urlVal, PrintWriter writer) {
	   boolean validURL = urlVal.isValid(testURL);
	   if (validURL) writer.println(testURL);
   }
}