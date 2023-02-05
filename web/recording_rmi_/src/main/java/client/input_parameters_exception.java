package client;

public class input_parameters_exception extends Exception{
    /**
     * Constructor with specified string
     * @param message string
     */
    public input_parameters_exception(String message) {
        super(message);
    }

    /**
     * Constructor with specified string and exception
     * @param message string
     * @param e error covered
     */
    public input_parameters_exception(String message, Throwable e){
        super(message, e);
    }

    @Override
    public String getMessage() {
        return super.getMessage();
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }
}
