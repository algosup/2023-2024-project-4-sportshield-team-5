# SportShield Sample API Manual

## 1. Purpose

This sample API aims to reproduce SportShield API behaviour from the client point of view. Its main purpose is to have a reliable solution to test the GRPS module communication over 2G network, but also to ensure the correct information are sent at the right time.

## 2. Installation

1. Download and install Node.JS and NPM: `https://nodejs.org/en/download`
2. Clone the repository using `git clone https://github.com/algosup/2023-2024-project-4-sportshield-team-5.git`
3. Open a command line at the root of the folder
4. Make this folder your working directory: `cd documents/quality-assurance/testing-resources/sportshield-api-example`
5. Install node-ts package on your whole system: `npm i -g node-ts`
6. Install all the dependencies related to this project: `npm i`
7. Run the server for your tests: `node-ts server.ts`

## 3. Usage

Every request which is made is logged in the command line to ensure requests have been received. Additionally, a log file logs every action to ensure traceability of the testing.
