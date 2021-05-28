#ifndef FIFO_H
#define FIFO_H


class FIFO{
    private:
    int _size;
    int _current_end;
    int _state;
    int *_data;
    

    public:
    FIFO(int limit);
    int add_data(float input);
    void force_add(float input);
    float pop(void);
    float read(int location);
    float read_end(void);
    int size_return(void);
    int end_loc_return(void);
    int state_return(void);
    void purge(void);

    private:
    void budge_up(void);
    void state_update(void);

};

#endif