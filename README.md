<h1>Philosophers</h1>
<p><strong>Philosophers</strong> is a project aimed at implementing the dining philosophers problem using multithreading and synchronization techniques. Developed as part of the curriculum at [Your Institution/University], this project explores concepts of concurrency, mutual exclusion, and deadlock avoidance.</p>
<h2>Features</h2>
<ul>
  <li>Implementation of the dining philosophers problem using threads and mutexes.</li>
  <li>Simulation of philosopher behavior including eating, thinking, and sleeping.</li>
  <li>Customizable number of philosophers and simulation parameters such as time to eat and sleep.</li>
  <li>Dynamic resource allocation and deallocation using mutex locks.</li>
</ul>
<h2>Getting Started</h2>
<h3>Prerequisites</h3>
<p>Ensure you have a Unix-like system with GCC and pthread library installed.</p>
<h3>Installation and Running</h3>
<ol>
  <li><strong>Clone the repository:</strong><br>
  <code>git clone https://github.com/vaismand/philosophers</code></li>
  <li><strong>Compile the program:</strong><br>
  <code>cd philo && make</code></li>
  <li><strong>Run the simulation:</strong><br>
  <code>./philo [number-of-philosophers] [time-to-die] [time-to-eat] [time-to-sleep] [optional: number-of-times-each-philosopher-must-eat]</code></li>
</ol>
<p>Explore the dynamics of dining philosophers and experiment with different parameters to observe their behavior!</p>