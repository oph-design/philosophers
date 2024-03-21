<a name="readme-top"></a>




<h1 align="center">Philosophers</h1>
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/oph-design/philosophers?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/oph-design/philosophers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/oph-design/philosophers?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/created-at/oph-design/philosophers?color=green" />
</p>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#examples">Examples</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<p align="center">
<img width="408" alt="Screen Shot 2024-03-21 at 3 49 37 PM" src="https://github.com/oph-design/philosophers/assets/115570424/790a907c-d141-49d4-9238-5237091f63bd">
</p>


Philosophers is an implementation of the philosopher problem in computer science. The setup is as follows.
A number of philosophers n sits on a round table. Each of alternately eats, sleeps and thinks. For food they have a bowl of spaghetti in the middle and each of them brings one fork. To eat from the bowl one philophers needs 2 forks, so they have to borrow the forks of their neighbour to be able to eat. </br>
On the start of the program it's determined how much time they need for eating and sleeping and also how much time can be pass between 2 meals before a philosopher dies. When a philosopher dies the simulation ends.</br>
To achieve this simulation it's mandatory to use threads, each philosopher following their own routine in their own thread. To prevent the philosophers from taking forks that are occupied by thier neighbours, the program uses mutex locks. Without mutexes the program would expirience the problem of Data Races, creating too much forks and causing read issues. </br>
Following example shows usage of mutex_locks in the main routine:
```c
static void	eat_sleep_think(t_philo *phil, int *running)
{
	pthread_mutex_lock(&phil->r_fork);
	print_action(take_fork, phil, running);
	pthread_mutex_lock(phil->l_fork);
	print_action(take_fork, phil, running);
	pthread_mutex_lock(&phil->param->eating);
	phil->has_eaten = get_time();
	pthread_mutex_unlock(&phil->param->eating);
	msleep(phil->param->time_to_eat);
	pthread_mutex_unlock(&phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	print_action(sleeping, phil, running);
	msleep(phil->param->time_to_sleep);
	print_action(thinking, phil, running);
}
```


<!-- GETTING STARTED -->
## Getting Started

The following contains a description of how to use the program. It is recommend to run in an unix (linux or mac) environment.
As installing make and compilers in windows can be quite tedious. You can find a tutorial and setting up an ubuntu virtual machine <a href="https://www.linkedin.com/pulse/how-install-ubuntu-virtualbox-md-emamul-mursalin/">here</a>

### Prerequisites

You need to have make and gcc installed. For mac you need also xcode to perform the installation.
* linux (Debian based)
  ```sh
  sudo apt install build-essential
  ```
* MAC-OS
  ```sh
  xcode-select --install
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/oph-design/philosophers.git
   ```
2. Build the executabel at the root of the repository
   ```sh
   make philosophers
   ```
4. Create alias for your shell, for easier usage
   ```sh
   echo "alias philo=\"path-to-executable\"" >> $HOME/.zshrc
   ```



<!-- USAGE EXAMPLES -->
## Usage

To execute the program you type the of the executable or your alias followed by the following parameters.
  * `PHILO_NUMBER` number of philophers at the table
  * `TIME_TO_DIE` time that needs to pass between 2 meals for a philosopher to die in miliseconds
  * `TIME_TO_EAT` tme it takes for a philosopher to eat in miliseconds
  * `TIME_TO_SLEEP` time it takes for a philosopher to sleep in miliseconds
  * `MUST_EAT` (optional) number of times each philopsher eats before the simulation stops
   
   ```sh
   ./philo 5 800 200 200
   ```
⚠️ Every computer is limited in the amount of operations it can parallelise. </br> Therefore it is recommended to use minimum time values of **60 miliseconds**, as well as a maximum **number of philosphers of 200**.


<!-- EXMAPLES -->
## Examples

Depending on the input values, there simulation that stop and simulations that run infinitely. </br>
<p></p>

infinite:
  ```sh
   ./philo 5 800 200 200
   ```
<p></p>

death:
  ```sh
   ./philo 3 500 200 400
   ```
<p></p>

stopping:
  ```sh
   ./philo 5 800 200 200 7
   ```
<p></p>

Output:
```console
❯ ./philo 3 310 150 150
0 philo 1: has taken a fork
0 philo 2: is thinking
0 philo 3: has taken a fork
0 philo 3: has taken a fork
0 philo 3: is eating
150 philo 3: is sleeping
150 philo 1: has taken a fork
150 philo 1: is eating
150 philo 2: has taken a fork
300 philo 3: is thinking
300 philo 3: has taken a fork
300 philo 2: has taken a fork
300 philo 1: is sleeping
300 philo 2: is eating
311 philo 3: died
```
<!-- CONTACT -->
## Contact

Ole-Paul Heinzelmann</br>
ole.paul.heinzelmann@protonmail.com </br>
<p></p>
<a href="https://www.linkedin.com/in/ole-paul-heinzelmann-a08304258/">
<img alt="linkedin shield" src="https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555" />
</a></br> 

<p align="right">(<a href="#readme-top">back to top</a>)</p>
