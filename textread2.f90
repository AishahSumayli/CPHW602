program read_file
    implicit none
    character(len=1000) :: line
    integer :: unit, iostat

    open(unit=10, file='oceans.txt', status='old', action='read', iostat=iostat)
    if (iostat /= 0) stop "Error opening file"

    do
        read(10, '(A)', iostat=iostat) line
        if (iostat /= 0) exit
        print *, line
    end do

    close(10)
end program read_file
