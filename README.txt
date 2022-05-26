/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name: Mandar Kapadia


Hours to complete assignment (optional): 6 hours


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

I think I did complete the whole assignment all of the values seem to get picked up and all of the Incompletes seem to get picked 
up.

/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
    boost::regex startingRegex(startingString, boost::regex::perl);
    boost::regex endRegex(endingString);

    std::string startingString = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}): \\(log.c.166\\) server started";
    std::string endingString = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}).([0-9]{3}):INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080";

    I created 2 regexs one is the starting string in which we look through the file using regex.
    The startingString and endingString say that I look for 4 chars between 0-9 - 2 between 0-2 then 2 char between 0-9. then it look for the time whech is 0-9 2 
    chars then : and then 2  char 0-9 2 chars and then : and  2 chars 0 - 9 which is the time. I next look at \\(log.c.166\\) server started for start and :Started SelectChannelConnector@0.0.0.0:9080".


/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
so in my approach I use regex_search and I search the file to find where my regex is true. if it is true 
then smash will have this in it which I will then use to add to my boot. I also get the time and put that into my begenning and ending then subtract end with begenning to then get the time.
I also have a checking bool which is there if a Incomplete boot was there which will only work if checking is true.



/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
I used the boost implentaion documenation,  I got help from an upperclassmen and worked with ravi patets



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/