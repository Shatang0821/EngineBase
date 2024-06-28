#ifndef _VISUALINTERFACE_H_
#define _VISUALINTERFACE_H_

class LayerInterface
{
private:
	int layer = 0;
public:
	LayerInterface();
	virtual ~LayerInterface();
	
	void SetLayer(int layer);
	int GetLayer() const;
};

#endif // !_VISUALINTERFACE_H_

