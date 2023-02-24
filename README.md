<h1 align="center">Open Cycle Time</h1>
<p align="center">
<a href="https://www.debian.org/"><img src="https://img.shields.io/badge/Debian-A81D33?style=for-the-badge&logo=debian&logoColor=white" /></a>
<a href="https://ubuntu.com/"><img src="https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white" /></a>
<a href="https://www.apple.com/macos/ventura/"><img src="https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white" /></a>
<a href="https://www.microsoft.com/en-us/windows"><img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" /></a>
</p>
<p align="center">
<a href="https://github.com/noncog/open-cycle-time/actions"><img src="https://github.com/noncog/open-cycle-time/actions/workflows/build.yml/badge.svg" /></a>
<a href="https://github.com/noncog/open-cycle-time/blob/main/LICENSE"><img src="https://img.shields.io/github/license/noncog/open-cycle-time?color=blue&style=flat-square" /></a>
</p>
<p align="center"><img src="./docs/images/open-cycle-time.svg" height="250"></p>
<p><code>Open Cycle Time</code> is a cross-platform video analysis tool for generating cycle times of manufacturing processes. It was made to provide a free and open-source tool that enable engineers to easily analyze their machinery without expensive sensors or software. Just use a video camera and this software instead!</p>
<h2>Requirements</h2>
<ul>
<li>Git</li>
<li>C++11</li>
<li>OpenGL 4.1</li>
<li>CMake 3.24+</li>
<li>Make (If using Linux/macOS and the command line)</li>
<li>xorg-dev (If using Linux and X11)</li>
<li>OpenCV 4.5+</li>
</ul>
<blockquote>
<b>Note: </b>Many of these requirements come bundled with your operating system and editor.
</blockquote>
<p>Open Cycle Time was made to be as portable as possible and easy to install, with only a single outside library dependency, namely OpenCV. All other libraries are fetched and built for you automatically, using CMake.</p>
<h3>Getting OpenCV</h3>
<p>OpenCV can be installed using a variety of methods. You can build the software from source, use a package manager, or get prebuilt binaries for your system. No matter the method, you just need to make sure that the variable <code>OpenCV_DIR</code> is set correctly in your environment or path variable, and it contains the files <code>OpenCVConfig-version.cmake</code> and <code>OpenCVConfig.cmake</code>. Without these, the software will not find OpenCV or build.</p>
<p>The simplest method to acquire OpenCV is to use a package manager for your operating system:</p>
<h4>Debian and Ubuntu</h4>
<pre><code>sudo apt install libopencv-dev</code></pre>
<p>Using this method, you do not need to update the environment variables.</p>
<h4>macOS</h4>
<p>Requires the <a href="https://brew.sh/">Homebrew</a> package manager.</p>
<pre><code>brew install opencv</code></pre>
<p>Using this method, you do not need to update the environment variables.</p>
<h4>Windows 10+</h4>
<p>Requires the <a href="https://chocolatey.org/">Chocolatey</a> package manager.</p>
<pre><code>choco install opencv</code></pre>
<p>Using this method, the default installation path is <code>C:\tools\opencv\build</code> and you should set the environment variable <code>OpenCV_DIR</code> to it.</p>
<h2>Getting Started</h2>
<p>With all of the requirements met, you're ready to install and build the software. There are multiple methods to accomplish this, use whichever you prefer.</p>
<blockquote>
<b>Note: </b><i>On Windows</i>, it's recommended to use an editor to get, build, and run the software since it bundles the dependencies and automates these tasks for you. This approach can also be used on Linux and macOS.
</blockquote>
<h3>Using the Command Line</h3>
<p>For all operating systems, to just get the software you can use Git:</p>
<pre><code>git clone https://github.com/noncog/open-cycle-time.git</code></pre>
<p>After cloning, for Linux and macOS, you can build and run the software using:</p>
<pre><code>cd open-cycle-time</code></pre>
<pre><code>make run</code></pre>
<blockquote>
<b>Note: </b><i>On Windows</i>, if you have Make, either through Chocolatey or MSYS2, you can also use the above method to build and run the software.
</blockquote>
<p>Alternatively, for all operating systems you can use one of the following editors to build and run the software.</p>
<h3>Using Visual Studio</h3>
<h4>If you've already cloned the repository:</h4>
<ol>
<li>Open the folder in Visual Studio.</li>
<li>Switch to the CMake Targets View in Solution Explorer.</li>
<li>Right click the target and select <code>build</code>.</li>
</ol>
<h4>If you want Visual Studio to clone the repository:</h4>
<ol>
<li>Select <code>Clone a repository</code>.</li>
<li>Enter: <code>https://github.com/noncog/open-cycle-time</code> and hit <code>clone</code>.</li>
<li>Switch to the CMake Targets View in Solution Explorer.</li>
<li>Right click the target and select <code>build</code>.</li>
</ol>
<h4>Additional Resources:</h4>
<ul>
<li><a href="https://learn.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2022">Visual Studio Tutorial: Open a Project from a Repo</a></li>
<li><a href="https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170 ">CMake Projects in Visual Studio</a></li>
</ul>
<h3>Using CLion</h3>
<h4>If you've already cloned the repository:</h4>
<ol>
<li>Open the folder in CLion.</li>
<li>From the <code>Run</code> menu select <code>Run 'open-cycle-time'</code>.</li>
</ol>
<h4>If you want CLion to clone the repository:</h4>
<ol>
<li>From the <code>File</code> menu, select <code>New</code> then <code>Project from Version Control...</code>.</li>
<li>Enter: <code>https://github.com/noncog/open-cycle-time</code> and hit <code>clone</code>.</li>
<li>From the <code>Run</code> menu select <code>Run 'open-cycle-time'</code>.</li>
</ol>
<h4>Troubleshooting:</h4>
<ul>
<li>If you can't run the project, in the <code>Build</code> menu select <code>Rebuild Project</code> until the CMake targets are populated.</li>
<li>If the wrong target is the default, in the Run menu select <code>Edit Configurations...</code> under <code>CMake Applications</code> choose <code>open-cycle-time</code>.</li>
</ul>