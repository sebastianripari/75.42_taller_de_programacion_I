/*
Figuras Geometricas.
*/

#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cmath>

class Rectangulo : public Gtk::DrawingArea {
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &context) {
        Gtk::Allocation allocation = this->get_allocation();
        int window_width = allocation.get_width();
        int window_height = allocation.get_height();
        float window_width_third = window_width * (1.0/3.0);
        float window_height_third = window_height * (1.0/3.0);
        context->move_to(window_width_third, window_height_third);
        context->line_to(2 * window_width_third, window_height_third);
        context->line_to(2 * window_width_third, 2 * window_height_third);
        context->line_to(window_width_third, 2 * window_height_third);
        context->line_to(window_width_third, window_height_third);
        context->set_source_rgb(1, 0, 0);
        context->fill();
        return true;
    }
};

class Elipse : public Gtk::DrawingArea {
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &context) {
        Gtk::Allocation allocation = get_allocation();
        int window_width = allocation.get_width();
        int window_height = allocation.get_height();
        context->scale(window_width, window_height);
        context->arc(0.5, 0.5, 0.5, 0, 2 * M_PI);
        context->fill();
        return true;
    }
};

class TrianguloEsquinaInferiorDerecha : public Gtk::DrawingArea {
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &context) {
        Gtk::Allocation allocation = this->get_allocation();
        int window_width = allocation.get_width();
        int window_height = allocation.get_height();
        context->move_to(0, window_height);
        context->line_to(window_width, window_height);
        context->line_to(window_width, 0);
        context->line_to(0, window_height);
        context->fill();
        return true;
    }
};

class Triangulo : public Gtk::DrawingArea {
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &context) {
        Gtk::Allocation allocation = this->get_allocation();
        int window_width = allocation.get_width();
        int window_height = allocation.get_height();
        context->move_to(window_width / 2, 0);
        context->line_to(window_width, window_height);
        context->line_to(0, window_height);
        context->line_to(window_width / 2, 0);
        context->set_source_rgb(1, 0, 0);
        context->fill();
        return true;
    }
};

class Rombo : public Gtk::DrawingArea {
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &context) {
        Gtk::Allocation allocation = this->get_allocation();
        int window_width = allocation.get_width();
        int window_height = allocation.get_height();
        context->move_to(window_width / 2, 0);
        context->line_to(window_width, window_height / 2);
        context->line_to(window_width / 2, window_height);
        context->line_to(0, window_height / 2);
        context->line_to(window_width / 2, 0);
        context->fill();
        return true;
    }
};

class Circulo : public Gtk::DrawingArea {
protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &context) {
	    Gtk::Allocation allocation = this->get_allocation();
    	int center_x = allocation.get_width() / 2;
    	int center_y = allocation.get_height() / 2;
    	int radius = allocation.get_height() / 2;
    	int start_angle = 0;
    	double end_angle = 2 * M_PI;
    	context->arc(center_x, center_y, radius, start_angle, end_angle);
    	context->fill();
    	return true;
	}
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create();
    Gtk::Window win;
    win.set_title("DrawingArea");

    /* TrianguloEsquinaInferiorDerecha */
    /*
    TrianguloEsquinaInferiorDerecha trianguloEsquinaInferiorDerecha;
    win.add(trianguloEsquinaInferiorDerecha);
    trianguloEsquinaInferiorDerecha.show();
    */  

    /* Triangulo */
    Triangulo triangulo;
    win.add(triangulo);
    triangulo.show();
    
    /* Circulo */
    /*
    Circulo circulo;
    win.add(circulo);
    circulo.show();
    */

    /* Rombo */
    /*
    Rombo rombo;
    win.add(rombo);
    rombo.show();
    */

    /* Elipse */
    /*
    Elipse elipse;
    win.add(elipse);
    elipse.show();
    */

    /* Rectangulo */
    /*
    Rectangulo rectangulo;
    win.add(rectangulo);
    rectangulo.show();
    */

    return app->run(win);
}