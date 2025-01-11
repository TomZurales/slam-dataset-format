class Cerial
{
public:
  virtual void serialize(std::ostream &os) = 0;
  virtual void deserialize(std::istream &is) = 0;
};