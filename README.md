
# Rewind Revitalize
A journaling app with a focus on mental health. Rate your mood, check stats, and see happy memories when you're blue.

[repl.it example of our program running](https://repl.it/@mstanley/RewindRevitalize)

**NOTE:** To run Rewind Revitalize on your own machine, simply use the included makefile to quickly compile and run the program! 


### Inspiration

Awareness and acceptance for mental health issues has been steadily increasing, as shown by the abundance of self help books, or the rise in popularity of yoga and meditation. Research has shown that [journaling is also an effective tool to aid combating many common mental health issues](https://www.urmc.rochester.edu/encyclopedia/content.aspx?ContentID=4552&ContentTypeID=1). For severe cases, therapy, medication, or more extensive measures should be taken as directed by a doctor or registered physician. However, for mild or moderate cases, there seems to be a lack of technological tools readily available for the everyday person who may be experiencing extensive difficulties, challenges, stress, or depressive episodes ([this is especially true for us STEM students!](https://www.sciencemag.org/careers/2015/05/depression-afflicts-almost-half-stem-graduate-students-uc-berkeley)).



### What it does

While there are many journaling apps on the market these days, only a few of them are focused on mental health. However all of these other  mental health journaling apps usually only focus on trying to form a community, or utilizing inspirational quotes as a quick pick-me-up. Our app will be unique in that it will combine the meditative and informational tracking of a journal with the proven research of [positive memory therapy](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3995858/) for the [treatment of anxiety or depression](https://news.mit.edu/2015/recalling-happier-memories-reverse-depression-0617).



### How this incorporates the theme

With the theme of the hackathon being **rewind**, we knew wanted to create a program that could *rewind time* somehow, but in a way that we felt important and could be useful to individuals on a personal level. So what better way of rewinding time then to rewind your memories and have a warming look back on the good times in your life? After discovering research that backed up our idea and how beneficial it could be, we knew we had our idea to move forward.
 



### How we built it

Our project was built entirely in C++, utilizing Git/Github for version control and easy collaboration between team members, and Slack for easy communication.



### Group members and their contributions

**Jordan** was the first one to dive into the project on Friday while everyone was at work, creating the Github repository and laying out the foundation and overall structure of the entire project. He also immediately started in on the getting the basic encryption and file input and output working. He would later work throughout the weekend to more fully implement the encryption and decryption process, the file handling, and was responsible for most of the functionality of the Journal class, as well as the work at the end to QA test and clean up the UI.

**Michael** started in on the project early Saturday, and worked all throughout the weekend. His contributions included fleshing out the Entry class and other journal entry related functions to establish the functionality of the journal entries themselves. This included manipulation of date/time strings, more helper functions, and the rewind() and addEntry() functions. He also worked throughout the end of the project QA testing and cleaning up comments and documentation to add the final polish.

**Andrew** was the one to submit the initial project proposal as well as this devpost! He started in on the project late Friday, but worked mostly throughout Saturday. He laid out the workings of main.cpp as well as some other key functions, including ones in the Journal class related to the verifying of username and passwords and helper functions for validation and menu options. His contributions can be summarized as the creation of the main menu, user interface and experience, this documentation, and some bug fixing and code organization, including getting the project to compile when it was in a state of disrepair. 



### Challenges we ran into

It was challenging because we all worked full time and there would only be a short window each day where we could all be online and coding at the same time. Most of the duration of the project consisted of different combinations of 2 of the 3 main contributors online together,  but we made it work. Slack made this process smoother as we could communicate through typed messages. If there was a group member who could not be online at the time then they could easily skim through the conversation and look at the changes on Github to get caught up to speed, and where we were at in the process or what needed to be worked on next.

Github was also a challenge at first, especially because we were all fairly new at using it and it took a day or so for us to become more familiar and comfortable with the tool.

There was also a small period of time where we had been implementing features without any particular order or plan, and this resulted in a program that would not compile. Thankfully, after some quick fixes and ironing out the wrinkles, we were able to quickly get back on track in order to finish up the rest of the project.



### Accomplishments that we're proud of

We set out to make a C++ project where you could write journal entries, see happy memories, and view your journaling statistics, but what we ended up with was everything and so much more. The end result was a much more fully featured application that could create different user accounts with usernames and passwords, store user data and their associated journal entries in encrypted files for privacy and protection, with an easy to use interface and a fantastic presentation that makes the most out of what you can do in a simple terminal window using only C++. 



### What we learned

We were very ambitious with all the features we wanted to implement, and we feel lucky that we did not encounter many major obstacles, bugs, 
or issues, and were able to complete the project on time. One of the tools we initially wanted to use was Asana in order for us to have more  efficient project management and task scheduling, but unfortunately the usage of this tool fell through after day one. More dedication to a tool like Asana may have been able to prevent small headaches like the time when we had an uncompilable program, but because there were only three of us on this smaller scale project, we worked well together and things turned out okay in the end.



### What's next for Rewind Revitalize

The next step for Rewind Revitalize would be to go bigger and better, and move beyond the limitations using C++ by itself. This would include creating a GUI for the user interface, a database and server for the storage of the user data instead of just in a file, and distributing the program on multiple platforms including a web-based application, desktop, and mobile! We also would like add more features that were not possible to implement using C++ alone, such as accessibility features like entering a voice recorded journal for the vision impaired or those who would have trouble typing the journal in text. Also, the ability to upload pictures or videos of the happy memory to show when using the rewind feature would make the positive memory therapy much more effective. The list of potential features we could add is endless, as what we have created already has huge potential.



##### Resources used


