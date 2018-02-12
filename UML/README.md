# UML diagrams

These are the UML diagrams for the elevator project.
They are made using [lucid chart](https://www.lucidchart.com/pages/examples/uml_diagram_tool), 
and are to be updated as the project developes. 
To get the latest version you can check the [lucid chart folder](https://www.lucidchart.com/invitations/accept/c6aceeb8-6069-4023-a487-88c48273557c)
directly. 

## sequence diagram scenario
* the elevator is empty, and standing still in the second floor with the door open
* one person request the elevator in the first floor, going up
* the elevator arrives, she orders transport to the third floor

for simplicity no other people can interact with the elevator during the sequence. 

## use case scenario

Main success scenario:
<ol>
  <li> System initializes elevator, elevator moves to a known state</li>
  <li>Passenger requests elevator at a floor</li>
  <li>System sets order lights on</li>
  <li>Elevator goes to floor, floor indicators are activated when passing</li>
  <li>Elevator opens door and closes after 3 sec</li>
  <li>System resets floor lights</li>
  <li>Passenger puts in elevator order</li>
  <li>System sets order light on</li>
  <li>Elevator goes to ordered floor, floor indicators are activated when passing</li>
  <li>Elevator opens door and closes after 3 sec</li>
  <li>System sets order lights off</li>
</ol>

### Extensions
<ol>
  <li> 7.a) Passenger holds stop button
    <ol type="i">
      <li> All orders are cancelled</li>
      <li> Elevator stops
        <ol type="a">
          <li> elevator stops at floor
            <ol type="i">
              <li> door opens, and closes three seconds after stop button is released</li>
            </ol type="i">
          </li>
        </ol type="a">
      </li>
    </ol type="i">
  </li>
  <li> 7.b) Another passenger requests elevator
    <ol type="a">
      <li>Process order if requested direction corresponds to direction of passing elevator </li>
    </ol type="a">
  </li>
</ol>

Vocab: floor lights, order, request, order lights

Primary Actor: Passenger

Pre-condition: elevator lies within floor 1 and 4

Guarantee: Carry out the passengers request, and orders

Trigger: Passenger presses request button
