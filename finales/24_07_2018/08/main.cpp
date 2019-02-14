/*
Enunciado.
Describa el concepto de loop de eventos (event loop) utilizado en programacion
orientada a eventos y en particular en entornos de interfaz grafica (GUIs).
*/

/*
Un "loop de eventos" es una logica en programacion que se encarga
de esperar eventos y luego despacharlos en un ciclo infinito. Estos 
eventos son provistos por un provedor interno o externo al programa.
*/

/*
En GUIs los eventos son por ejemplo los clicks del mouse. En el caso
de un click en un boton, este evento se lo deberiamos pasar al handler
de ese boton.
*/

int main() {
	while(true) {
		e = poll_event(event_provider);
		handle_event(e);
	}
	return 0;
}