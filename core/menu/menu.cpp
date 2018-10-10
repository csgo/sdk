#include "menu.hpp"
#include <sstream>

menu::menu(void)
{
	m_elements.push_back(new boolea("watermark", "msc_watermark"));
	m_elements.push_back(new float_slider("example_float", "flt1", 0.f, 1.1f, 0.1f, "f"));
	m_elements.push_back(new separator("esp"));
	m_elements.push_back(new combo("example_combo", "cmb", {"opt1", "opt2", "opt3"}));

	this->load();
}

float menu::_get(std::string var)
{
	for (auto &e : m_elements)
	{
		if (e->m_variable.compare(var) != 0){
			continue;
		}
		else{
			return e->m_value;
		}
	}

	return 0.0f;
}

void menu::draw_bool(boolea* draw)
{
	auto index = 0;

	for (; index < m_elements.size(); ++index)
	{
		if (m_elements[index] != (element*) draw)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	m_pos = vec2_t(30, 15 * (index + 1));

	auto enabled = !!atoi(std::to_string(draw->m_value).c_str());
	auto selected = (m_selected == index);
	auto font = render::get().main_font;

	auto color_selected = color(0, 175, 255);
	auto color_enabled = color(0, 175, 255);
	auto color_disabled = color(220, 220, 220);
	auto color_white = color(220, 220, 220);

	render::get().draw_filled_rect(m_pos.x, m_pos.y, m_pos.x + 220, 15, selected ? color(35, 35, 35) : color(40, 40, 40));
	render::get().draw_text(m_pos.x, m_pos.y, font, draw->m_name.c_str(), false, selected ? color_selected : color_white);
	render::get().draw_text(m_pos.x + 200, m_pos.y, font, enabled ? "on" : "off", false, enabled ? color_enabled : color_disabled);
}

void menu::draw_float(float_slider* draw)
{
	auto index = 0;

	for (; index < m_elements.size(); ++index)
	{
		if (m_elements[index] != (element*) draw) {
			continue;
		}
		else {
			break;
		}
	}

	auto _round = [] (float var) -> float {
		float value = (int) (var * 100 + .5);
		return (float) value / 100;
	};

	m_pos = vec2_t(30, 15 * (index + 1));

	auto enabled = (bool) (draw->m_value >= 0.1f);
	auto selected = (m_selected == index);
	auto font = render::get().main_font;

	auto color_selected = color(0, 175, 255);
	auto color_enabled = color(0, 175, 255);
	auto color_disabled = color(220, 220, 220);
	auto color_white = color(220, 220, 220);

	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2); // set # places after decimal
	ss << draw->m_value << draw->m_additive;

	render::get().draw_filled_rect(m_pos.x, m_pos.y, m_pos.x + 220, 30, selected ? color(35, 35, 35) : color(40, 40, 40));
	render::get().draw_text(m_pos.x, m_pos.y, font, draw->m_name.c_str(), false, selected ? color_selected : color_white);
	render::get().draw_text(m_pos.x + 200, m_pos.y, font, ss.str(), false, enabled ? color_enabled : color_disabled);
}

void menu::draw_int(int_slider* draw)
{
	auto index = 0;

	for (; index < m_elements.size(); ++index)
	{
		if (m_elements[index] != (element*) draw)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	m_pos = vec2_t(30, 15 * (index + 1));

	auto enabled = !!atoi(std::to_string(draw->m_value).c_str());
	auto selected = (m_selected == index);
	auto font = render::get().main_font;

	auto color_selected = color(0, 175, 255);
	auto color_enabled = color(0, 175, 255);
	auto color_disabled = color(220, 220, 220);
	auto color_white = color(220, 220, 220);

	auto value = std::string(std::to_string((int) draw->m_value));
	value.append(draw->m_additive);

	render::get().draw_filled_rect(m_pos.x, m_pos.y, m_pos.x + 220, 15, selected ? color(35, 35, 35) : color(40, 40, 40));
	render::get().draw_text(m_pos.x, m_pos.y, font, draw->m_name.c_str(), false, selected ? color_selected : color_white);
	render::get().draw_text(m_pos.x + 200, m_pos.y, font, value.c_str(), false, enabled ? color_enabled : color_disabled);
}

void menu::draw_combo(combo* draw)
{
	auto index = 0;

	for (; index < m_elements.size(); ++index)
	{
		if (m_elements[index] != (element*) draw)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	m_pos = vec2_t(30, 15 * (index + 1));

	auto enabled = !!atoi(std::to_string(draw->m_value).c_str());
	auto selected = (m_selected == index);
	auto font = render::get().main_font;

	auto color_selected = color(0, 175, 255);
	auto color_enabled = color(0, 175, 255);
	auto color_disabled = color(220, 220, 220);
	auto color_white = color(220, 220, 220);

	auto value = draw->m_container[(int) draw->m_value];

	render::get().draw_filled_rect(m_pos.x, m_pos.y, m_pos.x + 220, 15, selected ? color(35, 35, 35) : color(40, 40, 40));
	render::get().draw_text(m_pos.x, m_pos.y, font, draw->m_name.c_str(), false, selected ? color_selected : color_white);
	render::get().draw_text(m_pos.x + 200, m_pos.y, font, value.c_str(), false, enabled ? color_enabled : color_disabled);
}

void menu::draw_separator(separator* draw)
{
	auto index = 0;

	for (; index < m_elements.size(); ++index)
	{
		if (m_elements[index] != (element*) draw)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	m_pos = vec2_t(30, 15 * (index + 1));

	auto font = render::get().main_font;
	auto selected = (m_selected != index);
	auto color_white = color(220, 220, 220);

	render::get().draw_filled_rect(m_pos.x, m_pos.y, m_pos.x + 220, 30, color(40, 40, 40));
	render::get().draw_text(m_pos.x, m_pos.y, font, draw->m_name.c_str(), false, selected ? color_white : color(0, 175, 255));
}

// ugliest fn ever ;3
void menu::handle_input(void)
{
	auto get_key = [&] (int key)
	{
		static bool was_pressed[256];
		auto pressed = GetAsyncKeyState(key);

		if (!was_pressed[key] && pressed)
		{
			was_pressed[key] = true;
		}
		else if (was_pressed[key] && !pressed)
		{
			was_pressed[key] = false;
			return true;
		}

		return false;
	};


	if (get_key(VK_UP))
	{
		m_selected--;
	}

	else if (get_key(VK_DOWN))
	{
		m_selected++;
	}

	if (m_selected > m_elements.size() - 1) m_selected = 0;
	else if (m_selected < 0) m_selected = m_elements.size() - 1;

	auto element = m_elements[m_selected];

	if (element->m_type == element_type::boolea)
	{
		auto element_casted = (boolea*) element;

		if (get_key(VK_LEFT))
		{
			element_casted->m_value = 0;
		}
		else if (get_key(VK_RIGHT))
		{
			element_casted->m_value = 1;
		}
	}

	else if (element->m_type == element_type::float_slider)
	{
		auto element_casted = (float_slider*) element;

		if (get_key(VK_LEFT))
		{
			auto predicted = element_casted->m_value - element_casted->m_increment;

			if (predicted >= element_casted->m_min)
			{
				element_casted->m_value -= element_casted->m_increment;
			}
		}
		else if (get_key(VK_RIGHT))
		{
			auto predicted = element_casted->m_value + element_casted->m_increment;

			if (predicted <= element_casted->m_max)
			{
				element_casted->m_value += element_casted->m_increment;
			}
		}
	}

	else if (element->m_type == element_type::int_slider)
	{
		auto element_casted = (int_slider*) element;

		if (get_key(VK_LEFT))
		{
			auto predicted = element_casted->m_value - 1;

			if (predicted >= element_casted->m_min)
			{
				element_casted->m_value--;
			}
		}
		else if (get_key(VK_RIGHT))
		{
			auto predicted = element_casted->m_value + 1;

			if (predicted <= element_casted->m_max)
			{
				element_casted->m_value++;
			}
		}
	}

	else if (element->m_type == element_type::combo)
	{
		auto element_casted = (combo*) element;

		if (get_key(VK_LEFT))
		{
			auto predicted = element_casted->m_value - 1;

			if (predicted >= 0)
			{
				element_casted->m_value--;
			}
		}
		else if (get_key(VK_RIGHT))
		{
			auto predicted = element_casted->m_value + 1;

			if (predicted <= element_casted->m_container.size() - 1)
			{
				element_casted->m_value++;
			}
		}
	}
}

void menu::load(void)
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\sdk\\");
		file = std::string(path) + ("\\sdk\\config.sdk");
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto &e : m_elements)
	{
		char value[32] = {'\0'};

		GetPrivateProfileStringA("sdk", e->m_name.c_str(), "", value, 32, file.c_str());

		e->m_value = atof(value);
	}
}

void menu::save(void)
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\sdk\\");
		file = std::string(path) + ("\\sdk\\config.sdk");
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto &e : m_elements)
	{
		WritePrivateProfileStringA("sdk", e->m_name.c_str(), std::to_string(e->m_value).c_str(), file.c_str());
	}
}

void menu::tick(void)
{
	auto handle_open = [&] (void) {
		static bool was_pressed = false;
		auto pressed = GetAsyncKeyState(VK_INSERT);

		if (!was_pressed && pressed) {
			was_pressed = true;
		}
		else if (was_pressed && !pressed) {
			was_pressed = false;
			return true;
		}

		return false;
	};

	if (handle_open())
	{
		m_enabled = !m_enabled;

		if (m_enabled) {
			load();
		}
		else {
			save();
		}
	}

	if (!m_enabled) {
		return;
	}

	handle_input();

	for (auto &e : m_elements) {
		if (e->m_type == element_type::boolea) {
			draw_bool((boolea*) e);
		}
		else if (e->m_type == element_type::float_slider) {
			draw_float((float_slider*) e);
		}
		else if (e->m_type == element_type::int_slider) {
			draw_int((int_slider*) e);
		}
		else if (e->m_type == element_type::combo) {
			draw_combo((combo*) e);
		}
		else if (e->m_type == element_type::seperator) {
			draw_separator((separator*) e);
		}
	}
}