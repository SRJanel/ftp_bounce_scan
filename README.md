# FTP Bounce Scan
A quick implementation of a port scan using an ftp server as a proxy.
This small program connects to an ftp server and (ab)uses the PORT command and does a LIST right after in order to see if the port specified by PORT is open.  
It is to be noted that most of the servers or at least those who implement correctly RFC 2577 are not allowing to specify a port less than 1024 for security reasons. Furthermore most decent ftp servers disallow completely the use of PORT command or some just allow it only to connect to the same host you are connected from.  
In my opinion it's one of the easiest scans to perform in terms of code complexity.  
(Do not forget that this is as noisy as a Vanilla scan and detectable on the target side and on the proxy (FTP) server as well)  
