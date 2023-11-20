# Covid-19-info-management-system
C with Linked List:
A C program to store, analyze and update Covid-19 information about Greater Toronto Area (GTA) for the health ministry of Ontario has already been provided to you with several of its functions fully implemented. 
Data Collected:
• Regions:
  o Peel
  o York
  o Durham
• Towns:
o For Peel
  ▪ Brampton
  ▪ Mississauga
o For York
  ▪ Maple
  ▪ Vaughan
o For Durham
  ▪ Whitby
  ▪ Oshawa
• Race of head of the household which is supposed to be one of the following:
o African American, Asian, Caucasian, Indigenous, Other
• Number of people in the household—must be an integer greater than 0 and less than 12;
• Number of people tested positive for Covid-19 must not be more than number of people in the household;
• Number of people fully vaccinated—must not be more than number of people in the household.

The application has the following functions:
• Randomly populates information for one hundred households and store them in a linked list. 
  It should be ensured that random generator correctly match region and town pairs as given above and enter valid data for rest of the fields.
• Once the linked list of 100 nodes is populated with valid random data, display the entire list as shown in the screenshots which follow.
• Don’t forget to display the serial number starting from 1 in every output on the console that gives list of records.
• Ensure that output is displayed within 80 characters per line.
• Use a text-based menu driven interface to perform following actions based on user input in a loop.

A. Display records of only one:
  a. Race
  b. Region
  c. Town
B. Display household information of:
  a. Region and total Covid-19 cases tested positive per household over a threshold
  b. Region and town-wise ranking of total people vaccinated
C. An option to add a record
  a. The function must display the updated database after adding the record
D. An option to delete all records belonging to a triplet of a particular race, region, and town
  a. The function must display updated database after deleting the record
E. Store updated data on a file
F. Display data from the file
G. Exit the program
