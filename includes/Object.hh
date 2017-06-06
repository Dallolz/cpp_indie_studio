#ifndef OBJECT_HH_
# define OBJECT_HH_

enum	ObjectType
{
  OBJECT,
  BLOCK,
  BOMB,
  BONUS
};

class	Object
{
private:
  ObjectType	type;
public:
  Object();
  virtual ~Object();
  void	setType(ObjectType type);
  ObjectType	getType() const;
};

#endif /* !OBJECT_HH_ */
