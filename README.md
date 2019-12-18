# Eulerkreis
========

Das Projekt veranschaulicht den Ablauf des Algorithmus von
Fleury zum Finden eines Eulerkreises.

Benutzung:
	1. Erstellen neuer Knoten: 
	Durch drücken auf "Knoten erstellen" wird der Knotenmodus aktiviert.
	Durch Mausklick ins Zeichenfeld wird der Knoten erstellt.
	
	2. Erstellen einer Kante:
	Durch Klicken auf "Verbinden" wird der Kantenmodus aktiviert.
	Zwei Knoten werden ausgewählt und die Kante wird automatisch hinzugefügt.
	
	3. Löschen eines Knotens:
	Wird ein Knoten markiert und gelöscht (durch Klick auf Knoten im Modus "Knoten löschen" oder 		in allen Modi durch Klick auf Knoten und Entfernen Taste), so müssen auch alle an diesem 			Knoten anliegenden Kanten entfernt werden.
	
	4. Knoten verschieben:
	Die Knoten können zur besseen Übersicht auch verschoben werden. Dafür den Modus "Knoten 			verschieben" durch Klick aktivieren. 
	Zum Verschieben wird auf einen Knoten geklickt und gehalten und der Knoten dorthin verschoben, 	wo die Maus losgelassen wird. 
	
	5. Eulerkreis:
	Bei jedem "Paintevent" wird algorithmisch geprüft, ob der Graph ein Eulerkreis ist.
	Falls ja, wird der Graph in grün gezeichnet und mit der entsprechenden Nummer des Eulerkreises 	nummeriert.
	Ist er kein Eulerkreis, wird der Graph schwarz gezeichnet.
	
	
