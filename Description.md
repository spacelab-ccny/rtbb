# Root the (Ballot) Box

You will work in groups of 2 or 3 students on the semester project,
which will start on October 8 at 10am EDT. The goal will be to take a
voting machine and utilize the attacks and vulnerabilities taught in the
course to create a vulnerable voting machine with several back doors
that would allow a knowledgeable attacker to cheat in the election. Then
you will attack another group's voting machine, attempting to find all
of the vulnerabilities (intentional or not) in their system. Finally,
your group will present on both your machine and your experience
attacking a different machine.

## Part 1: The voting machine

The base of your project will be a vulnerable voting machine. You may
use the base voting machine code we provide or build your own. If you
choose to build your own, the voting system must have the following
features:

-   Be able to compile and run inside the class VM
    -   If this requires installing external dependencies, include those
        in a folder with your project so other teams can easily run your
        code
    -   If you need a database, use SQLite for ease of installation
-   Include multiple elections for various offices
    -   President, Congressional districts/constituencies, etc
    -   Do not have to be US government positions
-   A registration check to ensure a valid voter
-   A voting process where a registered voter makes their choices
    -   A legitimate voting system allows only one ballot per user
-   A "Cast Ballot" action where the user's votes are submitted,
    displaying the vote selections for each office
-   A process for an administrator to perform the following
    functionality:
    -   Create a new election
    -   Open an election for voting
    -   Close an election to prevent further votes (may be auto-closed
        at a given time)

The "machine" is not a physical device; consider, for example, a
"machine" that is a simple CGI-based web application, or a command-line
C program. The package that we will be providing has (minimally) the
above features. We encourage you to be creative, and add additional
features!

After your group finalizes the voting machine code, the second phase
will be to (covertly) add in vulnerabilities as back doors to the code.
Your group, in its final write-up, should clearly show (i.e., with
screenshot evidence) how the vulnerabilities can be used to compromise
the integrity of the voting machine. Remember that the goal of this
project is to change the outcome of the election, not just "break" the
application. This doesn't just mean changing vote totals -- there are
many ways to compromise an election, so be creative!

You will not be graded on the quality of the voting machine (outside of
it meeting this basic functionality), and you may use whatever sources
you want (cite them) to build legitimate voting machine code. What you
will be graded on is the quality of your back doors, the cleverness of
your inserted vulnerabilities, and your use of the techniques taught in
this class.

We expect *five vulnerabilities* explicitly coded into the voting
machine. Three of these must come directly from the ones studied in
class and the SEED Labs; the rest can either be a more difficult variant
of a previously-studied vulnerability, or a brand-new one entirely. We
encourage you to be creative in this as well. *You can (and should)
change the structure of the provided voting machine code to make it
vulnerable to attack in clever ways. Note also that the current
implementation is error-prone, and not robust.*

**What to turn in.** Building the vulnerable voting machine is half of
the project. This part is due on November 9 at 10pm EST via Gradescope.

-   A gzipped file with...
    -   All of your source code and build environment (such as
        makefiles) and installation instructions
    -   A write-up indicating how your voting machine works and what
        vulnerabilities you inserted and how you would exploit them
    -   Documentation with screenshots of your voting machine running
        correctly and then documentation with screenshots of your voting
        machine with a cheater changing the outcome
    -   A user manual for an unsuspecting user to use the voting machine
        correctly
-   A second gzipped distribution of just your source code and user
    manual. This will be used by another group in part 2 of the project.
    Make sure there are no comments explaining your vulnerabilities.

## Part 2: The red team

For this part of the project, you will be given a gzipped distribution
of source code and a user manual for another group's part 1 of the
project. Your team's goal is to perform a security analysis of the
voting machine. You will try to find all of the five vulnerabilities
that the other team put into their voting machine, plus any other
unintentional vulnerabilities. There will be extra credit if you find
vulnerabilities (with exploits) that they did not intend to create.

**What to turn in**. On November 30, by 10pm EST, you will submit a
report to Gradescope outlining all of the techniques you used to try to
find vulnerabilities, describing the vulnerabilities that you found and
if you were able to exploit them, and documentation (including
screenshots) of exploiting them.

## Part 3: The class presentation

Student presentations will be on December 1 and 3 in class. Both
sections will meet together in the same Zoom meeting, and each group
will present for 12 minutes. First you will describe your voting
machines and the backdoors and vulnerabilities that you inserted. Then,
you will describe the voting machine you were assigned to analyze and
you will explain what your red team analysis uncovered. Demos of both
systems would be useful. Provide a more in-depth exploration of the most
interesting (in your opinion) three vulnerabilities, and mention the
others you find.

After each presentation the group whose voting machine was red teamed in
the previous presentation will go next. Participation grades in the
course will take into account the attendance at the student
presentations on both days, especially for students who present on Dec
1.

**What to turn in**. All teams must turn in their project and their
final presentation slides to Gradescope by November 30 at 10pm EST, and
all teams must be ready to present on demand in class on either day.
