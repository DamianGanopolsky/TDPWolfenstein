#ifndef __WEAPON_PANEL_STATUS_H__
#define __WEAPON_PANEL_STATUS_H__

#include "Element_panel_status.h"
#include <string>	


class Weapon_panel_status : public Element_panel_status {
public:
	explicit Weapon_panel_status(SDL_Renderer*& renderer);
	Weapon_panel_status();
	Weapon_panel_status& operator=(Weapon_panel_status&& other);
	~Weapon_panel_status();
	
	virtual void copy_to_rederer(int id) override;
};

#endif