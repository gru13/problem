#define   NUM_JOB_TITLES        33
#define   NUM_DEPARTMENTS        7
#define   NUM_UNITS              4
#define   NUM_COUNTRIES          3
#define   NUM_CITIES            13

#define   MAX_LINE_SIZE        200

#define	  TSV_FILENAME			    "EmployeeSampleData.txt"
#define	  BIN_FILENAME			    "EmployeeDataReduced.bin"


// Job Titles 
char *JobTitles[NUM_JOB_TITLES] = {
	"Account Representative","Analyst","Analyst II","Automation Engineer","Business Partner",
	"Cloud Infrastructure Architect", "Computer Systems Manager", "Controls Engineer", 
	"Development Engineer", "Director", "Engineering Manager", "Enterprise Architect", 
	"Field Engineer", "HRIS Analyst", "IT Coordinator", "IT Systems Architect", "Manager", 
	"Network Administrator", "Network Architect", "Network Engineer", "Operations Engineer",
	"Quality Engineer", "Service Desk Analyst", "Solutions Architect", "Sr. Account Representative", 
	"Sr. Analyst", "Sr. Business Partner", "Sr. Manager", "System Administrator",
	"Systems Analyst", "Technical Architect", "Test Engineer", "Vice President"};

// Departments				
char *Departments[NUM_DEPARTMENTS] = {
	"Accounting", "Engineering", "Finance", "Human Resources", "IT", "Marketing", "Sales"};
#define IT	4

// Business Units				
char *BusinessUnits[NUM_UNITS] = {
	"Corporate", "Manufacturing", "Research & Development", "Specialty Products"};
#define R_AND_D   2

// Countries				
char *Countries[NUM_COUNTRIES] = {
	"Brazil", "China", "United States"};
#define CHINA   1
	
// Cities				
char *Cities[NUM_CITIES] = {
	"Austin", "Beijing", "Chengdu", "Chicago", "Chongqing", "Columbus", "Manaus", "Miami", 
	"Phoenix", "Rio de Janeiro", "Sao Paulo", "Seattle", "Shanghai"};
#define SEATTLE  11

	
