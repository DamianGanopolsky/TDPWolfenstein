#ifndef __FACE_PANEL_STATUS_H__
#define __FACE_PANEL_STATUS_H__

#include "Element_panel_status.h"
#include <string>	


class Face_panel_status : public Element_panel_status {
public:
	explicit Face_panel_status(SDL_Renderer*& renderer);
	Face_panel_status();
	Face_panel_status& operator=(Face_panel_status&& other);
	~Face_panel_status();
	
	virtual void copy_to_rederer(int health) override;
};

#endif